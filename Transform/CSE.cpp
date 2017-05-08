#include "llvm/Analysis/ValueTracking.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instruction.h"
#include "llvm/Pass.h"
#include <map>
using namespace llvm;

namespace {
    class CSE: public BasicBlockPass {
    public:
        static char ID;
        CSE(): BasicBlockPass(ID) {}

        bool runOnBasicBlock(BasicBlock &) override;

    private:
        bool isReusableExpr(Instruction &Inst) {
            return
                isa<BinaryOperator>(Inst) ||
                isa<CmpInst>(Inst) ||
                isa<ExtractElementInst>(Inst) ||
                isa<GetElementPtrInst>(Inst) ||
                isa<InsertElementInst>(Inst) ||
                isa<InsertValueInst>(Inst) ||
                isa<PHINode>(Inst) ||
                isa<SelectInst>(Inst) ||
                isa<ShuffleVectorInst>(Inst) ||
                isa<CastInst>(Inst) ||
                isa<ExtractValueInst>(Inst) ||
                isa<LoadInst>(Inst);
        }
    };
}

char CSE::ID = 0;
static RegisterPass<CSE> X("my-cse", "cyliang's local common subexpression elimination", false, false);

bool CSE::runOnBasicBlock(BasicBlock &BB) {
    // <NumOp, Op0, Op1, Op2, Op3, Op4> -> <Expr Value>
    std::map<std::tuple<unsigned, Value *, Value *, Value *, Value *, Value *>, Value *> ExprHash;

    auto OpOrNull = [](Instruction &Instr, unsigned OpIndex) -> Value * {
        return OpIndex < Instr.getNumOperands() ? Instr.getOperand(OpIndex) : nullptr;
    };

    bool changed = false;
    for (Instruction &Instr: BB) {
        if (Instr.mayWriteToMemory()) {
            ExprHash.clear();
        }

        if (!isReusableExpr(Instr)) {
            continue;
        }

        // Get opcode and operands of this instruction.
        auto Op = std::make_tuple(Instr.getOpcode(),
            OpOrNull(Instr, 0),
            OpOrNull(Instr, 1),
            OpOrNull(Instr, 2),
            OpOrNull(Instr, 3),
            OpOrNull(Instr, 4)
        );

        // Find if same expression already exists.
        auto Result = ExprHash.insert(std::make_pair(Op, &Instr));
        if (!Result.second) {
            Instr.replaceAllUsesWith(Result.first->second);
            changed = true;
        }
    }

    return changed;
}
