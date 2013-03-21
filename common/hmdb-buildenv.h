//
//  hmdb-buildenv.h
//  hmdb
//
//  Created by matsuki hidenori on 3/21/13.
//
//

#ifndef hmdb_hmdb_buildenv_h
#define hmdb_hmdb_buildenv_h

#if defined __clang__
/*--------------------------------
 | Clang frontend to LLVM        |
 --------------------------------*/
#include "../buildenv/llvm_clang/hmdb-cxx_dialect-llvm_clang.h"

#elif defined __llvm__
/*--------------------------------
 | GCC frontend to LLVM(LLVM-GCC)|
 --------------------------------*/
#include "../buildenv/llvm_gcc/hmdb-cxx_dialect-llvm_gcc.h"

#elif defined __GNUC__
/*--------------------------------
 | GNU GCC                       |
 --------------------------------*/
#include "../buildenv/gcc/hmdb-cxx_dialect-gcc.h"

#elif defined __INTEL_COMPILER
/*--------------------------------
 | Intel C++ Compiler            |
 --------------------------------*/
#include "../buildenv/icc/hmdb-cxx_dialect-icc.h"

#else
// Unknown compiler
#define HMDB_COMPILER_UNKNOWN
#endif

#endif
