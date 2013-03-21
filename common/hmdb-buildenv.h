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
#define HMDB_COMPILER_LLVM_CLANG

#elif defined __llvm__
/*--------------------------------
 | GCC frontend to LLVM(LLVM-GCC)|
 --------------------------------*/
#define HMDB_COMPILER_LLVM_GCC

#elif defined __GNUC__
/*--------------------------------
 | GNU GCC                       |
 --------------------------------*/
#define HMDB_COMPILER_GCC

//#elif defined __INTEL_COMPILER
/*--------------------------------
 | Intel C++ Compiler            |
 --------------------------------*/
//#define HMDB_COMPILER_INTEL

#else
// Unknown compiler
#define HMDB_COMPILER_UNKNOWN
#endif

#endif
