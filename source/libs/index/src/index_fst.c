/*
 * Copyright (c) 2019 TAOS Data, Inc. <jhtao@taosdata.com>
 *
 * This program is free software: you can use, redistribute, and/or modify
 * it under the terms of the GNU Affero General Public License, version 3
 * or later ("AGPL"), as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "index_fst.h"


FstUnFinishedNodes *fstUnFinishedNodesCreate() {
  FstUnFinishedNodes *nodes = malloc(sizeof(FstUnFinishedNodes));
  if (nodes == NULL) { return NULL; }

  nodes->stack = (SArray *)taosArrayInit(64, sizeof(FstBuilderNodeUnfinished));
  fstUnFinishedNodesPushEmpty(nodes, false);
  return nodes;
}
void unFinishedNodeDestroyElem(void* elem) {
  FstBuilderNodeUnfinished *b = (FstBuilderNodeUnfinished*)elem;
  fstBuilderNodeDestroy(b->node); 
  free(b->last); 
}  
void fstUnFinishedNodesDestroy(FstUnFinishedNodes *nodes) {
  if (nodes == NULL) { return; } 

  taosArrayDestroyEx(nodes->stack, unFinishedNodeDestroyElem); 
  free(nodes);
}

void fstUnFinishedNodesPushEmpty(FstUnFinishedNodes *nodes, bool isFinal) {
  FstBuilderNode *node = malloc(sizeof(FstBuilderNode));
  node->isFinal     = isFinal;
  node->finalOutput = 0;
  node->trans       = NULL;

  FstBuilderNodeUnfinished un = {.node = node, .last = NULL}; 
  taosArrayPush(nodes->stack, &un);
  
}
FstBuilderNode *fstUnFinishedNodesPopRoot(FstUnFinishedNodes *nodes) {
  assert(taosArrayGetSize(nodes->stack) == 1);

  FstBuilderNodeUnfinished *un = taosArrayPop(nodes->stack);
  assert(un->last == NULL); 
  return un->node;  
}

FstBuilderNode *fstUnFinishedNodesPopFreeze(FstUnFinishedNodes *nodes, CompiledAddr addr) {
  FstBuilderNodeUnfinished *un = taosArrayPop(nodes->stack);
  fstBuilderNodeUnfinishedLastCompiled(un, addr);
  free(un->last); // TODO add func FstLastTransitionFree()
  return un->node; 
}

FstBuilderNode *fstUnFinishedNodesPopEmpty(FstUnFinishedNodes *nodes) {
  FstBuilderNodeUnfinished *un = taosArrayPop(nodes->stack);
  assert(un->last == NULL); 
  return un->node;  
  
}
void fstUnFinishedNodesSetRootOutput(FstUnFinishedNodes *nodes, Output out) {
  FstBuilderNodeUnfinished *un = taosArrayGet(nodes->stack, 0);
  un->node->isFinal     = true;
  un->node->finalOutput = out;
  //un->node->trans       = NULL;  
} 
void fstUnFinishedNodesTopLastFreeze(FstUnFinishedNodes *nodes, CompiledAddr addr) {
  size_t sz = taosArrayGetSize(nodes->stack) - 1; 
  FstBuilderNodeUnfinished *un = taosArrayGet(nodes->stack, sz);
  fstBuilderNodeUnfinishedLastCompiled(un, addr);
}
void fstUnFinishedNodesAddSuffix(FstUnFinishedNodes *nodes, FstSlice bs, Output out) {
  FstSlice *s = &bs;
  if (s->data == NULL || s->dLen == 0 || s->start > s->end) {
    return;
  }
  size_t sz = taosArrayGetSize(nodes->stack) - 1; 
  FstBuilderNodeUnfinished *un = taosArrayGet(nodes->stack, sz);
  assert(un->last == NULL);

  
  
  //FstLastTransition *trn = malloc(sizeof(FstLastTransition)); 
  //trn->inp = s->data[s->start]; 
  //trn->out = out;
  un->last = fstLastTransitionCreate(s->data[s->start], out); 

  for (uint64_t i = s->start; i <= s->end; i++) {
    FstBuilderNode *n = malloc(sizeof(FstBuilderNode));
    n->isFinal     = false;
    n->finalOutput = 0;
    n->trans       = NULL;
    
    //FstLastTransition *trn = malloc(sizeof(FstLastTransition)); 
    //trn->inp = s->data[i];
    //trn->out = out; 
    FstLastTransition *trn = fstLastTransitionCreate(s->data[i], out);

    FstBuilderNodeUnfinished un = {.node = n, .last = trn}; 
    taosArrayPush(nodes->stack, &un); 
  }
  fstUnFinishedNodesPushEmpty(nodes, true);  
}


uint64_t fstUnFinishedNodesFindCommPrefix(FstUnFinishedNodes *node, FstSlice bs) {
  FstSlice *s = &bs;

  size_t lsz = (size_t)(s->end - s->start + 1);          // data len 
  size_t ssz = taosArrayGetSize(node->stack);  // stack size
    
  uint64_t count = 0;
  for (size_t i = 0; i < ssz && i < lsz; i++) {
    FstBuilderNodeUnfinished *un = taosArrayGet(node->stack, i); 
    if (un->last->inp == s->data[s->start + i]) {
      count++;
    } else {
      break;
    } 
  }
  return count;
}
uint64_t fstUnFinishedNodesFindCommPrefixAndSetOutput(FstUnFinishedNodes *node, FstSlice bs, Output in, Output *out) {
  FstSlice *s = &bs;

  size_t lsz = (size_t)(s->end - s->start + 1);          // data len 
  size_t ssz = taosArrayGetSize(node->stack);  // stack size

  uint64_t res = 0;
  for (size_t i = 0; i < lsz && i < ssz; i++) {
    FstBuilderNodeUnfinished *un = taosArrayGet(node->stack, i);

    FstLastTransition *last = un->last; 
    if (last->inp == s->data[s->start + i]) {
      uint64_t commPrefix = last->out;      
      uint64_t addPrefix  = last->out - commPrefix; 
      out = out - commPrefix; 
      last->out = commPrefix;
      if (addPrefix != 0) {
        fstBuilderNodeUnfinishedAddOutputPrefix(un, addPrefix);  
      }
    } else {
      break;
    }
  }   
  return res;
} 


FstState fstStateCreate(FstSlice* date, CompiledAddr addr) {
  FstState fs =  {.state = EmptyFinal, .val = 0}; 
  if (addr == EMPTY_ADDRESS) {
    fs.state = EmptyFinal; 
    fs.val   = 0;
    return fs; 
  }
  
  FstSlice *s = date;
  uint8_t v = s->data[addr]; 
  uint8_t t = (v & 0b11000000) >> 6;
  if (t == 0b11) {
    fs.state = OneTransNext;
    fs.val   = v;
  } else if (t == 0b10) {
    fs.state = OneTrans;
    fs.val   = v;
  } else {
    fs.state = AnyTrans;
    fs.val   = v;
  }
  return fs;
}

// fst node function 

FstNode *fstNodeCreate(int64_t version, CompiledAddr addr, FstSlice *slice) {
  FstNode *n = (FstNode *)malloc(sizeof(FstNode)); 
  if (n == NULL) { return NULL; }

  FstState st = fstStateCreate(slice, addr);  

  if (st.state == EmptyFinal) {
     n->data    = fstSliceCreate(NULL, 0);   
     n->version = version;
     n->state   = st;  
     n->start   = EMPTY_ADDRESS;
     n->end     = EMPTY_ADDRESS;  
     n->isFinal = true; 
     n->nTrans  = 0;
     n->sizes   = 0;  
     n->finalOutput = 0;  
  } else if (st.state == OneTransNext) {
     n->data    = fstSliceCopy(slice, 0, addr);     
     n->version = version;
     n->state   = st;  
     n->start   = addr;
     n->end     = addr; //? s.end_addr(data); 
     n->isFinal = false;
     n->sizes   = 0;
     n->nTrans  = 0;
     n->finalOutput = 0;
  } else if (st.state == OneTrans) {
     uint64_t sz; // fetch sz from addr
     n->data    = fstSliceCopy(slice, 0, addr); 
     n->version = version; 
     n->state   = st; 
     n->start   = addr;
     n->end     = addr; // s.end_addr(data, sz);
     n->isFinal = false; 
     n->nTrans  = 1; 
     n->sizes   = sz;   
     n->finalOutput = 0; 
  } else {
     uint64_t sz;    // s.sizes(data)
     uint32_t nTrans; // s.ntrans(data)  
     n->data    = *slice; 
     n->version = version;
     n->state   = st;
     n->start   = addr;
     n->end     = addr; // s.end_addr(version, data, sz, ntrans);
     n->isFinal = false; // s.is_final_state();
     n->nTrans  = nTrans;
     n->sizes   = sz;
     n->finalOutput = 0; // s.final_output(version, data, sz, ntrans);
  }
   return n; 
}
void fstNodeDestroy(FstNode *node) {
  free(node);
}
FstTransitions* fstNodeTransitions(FstNode *node) {
  FstTransitions *t = malloc(sizeof(FstTransitions));
  if (NULL == t) {
    return NULL; 
  }
  FstRange range = {.start = 0, .end = FST_NODE_LEN(node)};
  t->range = range;
  t->node  = node;
  return t; 
} 

// Returns the transition at index `i`. 
bool fstNodeGetTransitionAt(FstNode *node, uint64_t i, FstTransition *trn) {
  bool s = true;
  //FstState st = node->state;
  if (FST_STATE_ONE_TRNAS_NEXT(node)) {
    trn->inp  = 0; 
    trn->out  = 0;
    trn->addr = 0; 
  } else if (FST_STATE_ONE_TRNAS(node)) {
    trn->inp  = 0;    
    trn->out  = 0;
    trn->addr = 0; 
  } else if (FST_STATE_ANY_TRANS(node)) {
    trn->inp  = 0;
    trn->out  = 0;
    trn->addr = 0; 
  } else {
    s = false;
  }
  return s;
} 

// Returns the transition address of the `i`th transition
bool fstNodeGetTransitionAddrAt(FstNode *node, uint64_t i, CompiledAddr *res) {
  bool s = true;
  if (FST_STATE_ONE_TRNAS_NEXT(node)) {

  } else if (FST_STATE_ONE_TRNAS(node)) {

  } else if (FST_STATE_ANY_TRANS(node)) {

  } else if (FST_STATE_EMPTY_FINAL(node)){
    s = false;
  } else {
    assert(0);
  }
  return s;
}

//  Finds the `i`th transition corresponding to the given input byte.
//  If no transition for this byte exists, then `false` is returned. 
bool fstNodeFindInput(FstNode *node, uint8_t b, uint64_t *res) {
  bool s = true;
  uint8_t input; // get s.input
  FstState fs = node->state;
  if (FST_STATE_ONE_TRNAS_NEXT(node)) {
    if (b == input) { *res = 0; } 
    else { return s ; }
  } else if (FST_STATE_ONE_TRNAS(node)) {
    if (b == input) { *res = 0; }
    else {return s;}
  } else if (FST_STATE_ANY_TRANS(node)) {
     
  } else if (FST_STATE_EMPTY_FINAL(node)) {
    s = false;
  } 
  return s;
} 

bool fstNodeCompile(FstNode *node, void *w, CompiledAddr lastAddr, CompiledAddr addr, FstBuilderNode *builderNode) {
  size_t sz = taosArrayGetSize(builderNode->trans);  
  assert(sz < 256);
  if (sz == 0 && builderNode->isFinal && builderNode->finalOutput == 0) {
    return true; 
  } else if (sz != 1 || builderNode->isFinal) {
    // AnyTrans->Compile(w, addr, node);
  } else {
    FstTransition *tran = taosArrayGet(builderNode->trans, 0);   
    if (tran->addr == lastAddr && tran->out == 0) {
       //OneTransNext::compile(w, lastAddr, tran->inp);
       return true;
    } else {
      //OneTrans::Compile(w, lastAddr, *tran);
       return true;
    } 
  } 
  return true; 
} 


FstBuilder *fstBuilderCreate(void *w, FstType ty) {
  FstBuilder *b = malloc(sizeof(FstBuilder));  
  if (NULL == b) { return b; }

   
  b->wrt = fstCountingWriterCreate(w);
  b->unfinished = fstUnFinishedNodesCreate();   
  b->registry   = fstRegistryCreate(10000, 2) ;
  b->last       = fstSliceCreate(NULL, 0);
  b->lastAddr   = NONE_ADDRESS; 
  b->len        = 0;
  return b;
}
void fstBuilderDestroy(FstBuilder *b) {
  if (b == NULL) { return; }

  fstCountingWriterDestroy(b->wrt); 
  fstUnFinishedNodesDestroy(b->unfinished); 
  fstRegistryDestroy(b->registry);
  free(b);
}


bool fstBuilderInsert(FstBuilder *b, FstSlice bs, Output in) {
  OrderType t = fstBuilderCheckLastKey(b, bs, true);  
  if (t == Ordered) {
    // add log info
    fstBuilderInsertOutput(b, bs, in); 
    return true; 
  } 
  return false;
}

void fstBuilderInsertOutput(FstBuilder *b, FstSlice bs, Output in) {
   FstSlice *s = &bs;
   if (fstSliceEmpty(s)) {
     b->len = 1; 
     fstUnFinishedNodesSetRootOutput(b->unfinished, in);
     return;
   }
   Output out; 
   uint64_t prefixLen;
   if (in != 0) { //if let Some(in) = in 
      prefixLen = fstUnFinishedNodesFindCommPrefixAndSetOutput(b->unfinished, bs, in, &out);  
   } else {
      prefixLen = fstUnFinishedNodesFindCommPrefix(b->unfinished, bs);
      out = 0;
   }

   if (prefixLen == FST_SLICE_LEN(s)) {
      assert(out != 0);
      return;
   }

   b->len += 1;
   fstBuilderCompileFrom(b, prefixLen); 
   
   FstSlice sub = fstSliceCopy(s, prefixLen, s->end);
   fstUnFinishedNodesAddSuffix(b->unfinished, sub, out);
   return;
 }

OrderType fstBuilderCheckLastKey(FstBuilder *b, FstSlice bs, bool ckDup) {
  FstSlice *input = &bs;
  if (fstSliceEmpty(&b->last)) {
    // deep copy or not
    b->last = fstSliceCopy(&bs, input->start, input->end);
  } else {
    int comp = fstSliceCompare(&b->last, &bs);
    if (comp == 0 && ckDup) {
      return DuplicateKey;  
    } else if (comp == 1) {
      return OutOfOrdered;
    }
    // deep copy or not
    b->last = fstSliceCopy(&bs, input->start, input->end); 
  }       
  return Ordered;
} 
void fstBuilderCompileFrom(FstBuilder *b, uint64_t istate) {
  CompiledAddr addr = NONE_ADDRESS;
  while (istate + 1 < FST_UNFINISHED_NODES_LEN(b->unfinished)) {
    FstBuilderNode *n = NULL;
    if (addr == NONE_ADDRESS) {
      n = fstUnFinishedNodesPopEmpty(b->unfinished);
    } else {
      n = fstUnFinishedNodesPopFreeze(b->unfinished, addr);
    }
    addr =  fstBuilderCompile(b, n);
    assert(addr != NONE_ADDRESS);      
    fstBuilderNodeDestroy(n);
  }
  fstUnFinishedNodesTopLastFreeze(b->unfinished, addr);
  return; 
}
CompiledAddr fstBuilderCompile(FstBuilder *b, FstBuilderNode *bn) {
  if (FST_BUILDER_NODE_IS_FINAL(bn) 
      && FST_BUILDER_NODE_TRANS_ISEMPTY(bn) 
      && FST_BUILDER_NODE_FINALOUTPUT_ISZERO(bn)) {
    return EMPTY_ADDRESS; 
  }
  FstRegistryEntry *entry = fstRegistryGetEntry(b->registry, bn); 
  if (entry->state == FOUND) { 
    CompiledAddr ret = entry->addr;
    fstRegistryEntryDestroy(entry);
    return ret;
  } 
  CompiledAddr startAddr = (CompiledAddr)(FST_WRITER_COUNT(b->wrt));

  fstBuilderNodeCompileTo(bn, b->wrt, b->lastAddr, startAddr);  
  b->lastAddr =  (CompiledAddr)(FST_WRITER_COUNT(b->wrt) - 1);  
  if (entry->state == NOTFOUND) {
    FST_REGISTRY_CELL_INSERT(entry->cell, b->lastAddr);    
  }
  fstRegistryEntryDestroy(entry);
  
  return b->lastAddr;  
}




FstSlice fstNodeAsSlice(FstNode *node) {
  FstSlice *slice = &node->data; 
  FstSlice s = fstSliceCopy(slice, slice->end, slice->dLen - 1);   
  return s; 
}

FstLastTransition *fstLastTransitionCreate(uint8_t inp, Output out) {
  FstLastTransition *trn = malloc(sizeof(FstLastTransition));
  if (trn == NULL) { return NULL; }

  trn->inp = inp;
  trn->out = out;
  return trn;
}

void fstLastTransitionDestroy(FstLastTransition *trn) {
  free(trn);
}
void fstBuilderNodeUnfinishedLastCompiled(FstBuilderNodeUnfinished *unNode, CompiledAddr addr) {
  FstLastTransition *trn = unNode->last;       
  if (trn == NULL) { return; }  

  FstTransition t = {.inp = trn->inp, .out = trn->out, .addr = addr};      
  taosArrayPush(unNode->node->trans, &t); 
  return;
}

void fstBuilderNodeUnfinishedAddOutputPrefix(FstBuilderNodeUnfinished *unNode, Output out) {
  if (FST_BUILDER_NODE_IS_FINAL(unNode->node)) {
    unNode->node->finalOutput += out;  
  }
  size_t sz = taosArrayGetSize(unNode->node->trans);
  for (size_t i = 0; i < sz; i++) {
    FstTransition *trn = taosArrayGet(unNode->node->trans, i); 
    trn->out += out;
  }
  if (unNode->last) {
    unNode->last->out += out;  
  }
  return;
}


