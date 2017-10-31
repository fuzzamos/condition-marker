// LLVM loop trip count calculation tester
//
// Portions copyright 2017 National University of Singapore
// See LICENSE.md for the license information.
//
// Based on discussions in these articles:
// http://lists.llvm.org/pipermail/llvm-dev/2017-May/113143.html
// http://stackoverflow.com/questions/13834364/how-to-get-loop-bounds-in-llvm
// http://lists.llvm.org/pipermail/llvm-dev/2011-March/038502.html
// https://groups.google.com/forum/#!topic/llvm-dev/1oNNBPMSqBg

#include "llvm/InitializePasses.h"
#include "llvm/Pass.h"
#include "llvm/PassManager.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/ScalarEvolution.h"
#include "llvm/Analysis/ScalarEvolutionExpressions.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/SourceMgr.h"

#include <set>
#include <vector>

/*
 * Main.
 */
int main(int argc, char **argv)
{
  if (argc < 2) {
    llvm::errs() << "Filename unspecified\n";
    return 1;
  }

  llvm::LLVMContext &Context = llvm::getGlobalContext();
  llvm::SMDiagnostic Err;
  llvm::Module *M = ParseIRFile(argv[1], Err, Context);

  if (M == 0) {
    llvm::errs() << "ERROR: failed to load " << argv[0] << "\n";
    return 1;
  }

  for (auto &F: *M) {
	  for (auto &BB: F) {
		  for (auto &I: BB) {
			  I.dump();
		  }
	  }
  }
	
  return 0;
}

