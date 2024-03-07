#pragma once
#include "dominant.hpp"

class gvn {
private:
  dominance *m_dom;
  std::unordered_map<Value *, size_t> Hash_Tab; //指令对应的hashNumber
  std::vector<std::pair<Value *, Value *>> ValueNumer; // VN array
  std::set<User *> PinnedInst;
  Function *m_func;
  std::vector<BasicBlock *> RPO;
  std::unordered_set<BasicBlock *> visited;
  bool HasUndefVal = false;
public:
  gvn(dominance *dom, Function *func)
      : m_dom(dom), Hash_Tab{}, PinnedInst{}, m_func(func) {}

  void GCM();
  void GVN();
  void init_pass();
  void Schedule_Early(User *inst);
  void Schedule_Late(User *inst);
  bool IsPinned(User *inst);
  void caculateRPO(BasicBlock *bb);
  int OptConstBinary_INT(BinaryInst::Operation op, Value *a, Value *b);
  float OptConstBinary_Float(BinaryInst::Operation op, Value *a, Value *b);
  Value *Special_Opt(BinaryInst::Operation op, Value *a, Value *b);
  Value *Find_Equal(Value *inst);
  Value *SimplifyBinaryInst(BinaryInst *inst);
  Value *SimplifyCall(CallInst *inst);
  Value *SimplifyGEPInst(GetElementPtrInst *inst);
  Value *SimplifyPhiInst(PhiInst *inst);
  bool HaveSideEffect(Function *func);
};