#include "llvm/ADT/DenseSet.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instruction.h"
#include "llvm/Pass.h"
#include <queue>
using namespace llvm;

namespace {
    class CSE: public BasicBlockPass {
    public:
        static char ID;
        CSE(): BasicBlockPass(ID) {}

        bool runOnBasicBlock(BasicBlock &) override;

    };
}

char CSE::ID = 0;
static RegisterPass<CSE> X("my-cse", "cyliang's common subexpression elimination", false, false);
