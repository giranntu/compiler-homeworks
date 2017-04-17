#include "llvm/ADT/DenseSet.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instruction.h"
#include "llvm/Pass.h"
#include <queue>
using namespace llvm;

namespace {
    class DCE: public FunctionPass {
    public:
        static char ID;
        DCE(): FunctionPass(ID) {}

        bool runOnFunction(Function &) override;

    private:
        /// Return whether an instruction is a critical instruction.
        bool isCritical(Instruction &I) {
            return I.isTerminator() || I.mayHaveSideEffects();
        }
    };
}

char DCE::ID = 0;
static RegisterPass<DCE> X("my-dce", "cyliang's dead code elimination", false, false);

bool DCE::runOnFunction(Function &F) {
    std::queue<Instruction *> WorkList;
    DenseSet<Instruction *> Marked;

    // Find critical instructions.
    for (BasicBlock &BB: F) {
        for (Instruction &Inst: BB) {
            if (isCritical(Inst)) {
                Marked.insert(&Inst);
                WorkList.push(&Inst);
            }
        }
    }

    // Consume the work list.
    while (!WorkList.empty()) {
        // Pop one work.
        Instruction &Inst = *WorkList.front();
        WorkList.pop();

        // Iteratively mark operands' defines.
        for (Use &U: Inst.operands()) {
            Instruction *Def = dyn_cast<Instruction>(U.get());

            // Mark and keep work on the operand's define.
            if (Marked.insert(Def).second) {
                WorkList.push(Def);
            }
        }
    }

    // Delete not marked instructions.
    bool Deleted = false;
    for (BasicBlock &BB: F) {
        for (auto InstIt = BB.begin(), InstEnd = BB.end(); InstIt != InstEnd; ) {
            Instruction *Inst = &*InstIt;
            ++InstIt;

            if (!Marked.count(Inst)) {
                Inst->eraseFromParent();
                Deleted = true;
            }
        }
    }

    return Deleted;
}
