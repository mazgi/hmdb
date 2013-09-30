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
#define HMDB_COMPILER "Unknown"
#endif

/* C++ dialect { */
#ifndef HMDB_CXX_DIALECT_CXX98
#define HMDB_CXX_DIALECT_CXX98 (__cplusplus >= 199711L)
#endif
#ifndef HMDB_CXX_DIALECT_CXX11
#define HMDB_CXX_DIALECT_CXX11 (__cplusplus >= 201103L)
#endif
/* } C++ dialect */

/* C++ feature { */
// cxx_exceptions
#ifndef HMDB_CXX_FEATURE_CXX_EXCEPTIONS
#define HMDB_CXX_FEATURE_CXX_EXCEPTIONS 0
#endif
// cxx_rtti
#ifndef HMDB_CXX_FEATURE_CXX_RTTI
#define HMDB_CXX_FEATURE_CXX_RTTI 0
#endif
// cxx_access_control_sfinae
#ifndef HMDB_CXX_FEATURE_CXX_ACCESS_CONTROL_SFINAE
#define HMDB_CXX_FEATURE_CXX_ACCESS_CONTROL_SFINAE 0
#endif
// cxx_alias_templates
#ifndef HMDB_CXX_FEATURE_CXX_ALIAS_TEMPLATES
#define HMDB_CXX_FEATURE_CXX_ALIAS_TEMPLATES 0
#endif
// cxx_alignas
#ifndef HMDB_CXX_FEATURE_CXX_ALIGNAS
#define HMDB_CXX_FEATURE_CXX_ALIGNAS 0
#endif
// cxx_attributes
#ifndef HMDB_CXX_FEATURE_CXX_ATTRIBUTES
#define HMDB_CXX_FEATURE_CXX_ATTRIBUTES 0
#endif
// cxx_constexpr
#ifndef HMDB_CXX_FEATURE_CXX_CONSTEXPR
#define HMDB_CXX_FEATURE_CXX_CONSTEXPR 0
#endif
// cxx_decltype
#ifndef HMDB_CXX_FEATURE_CXX_DECLTYPE
#define HMDB_CXX_FEATURE_CXX_DECLTYPE 0
#endif
// cxx_default_function_template_args
#ifndef HMDB_CXX_FEATURE_CXX_DEFAULT_FUNCTION_TEMPLATE_ARGS
#define HMDB_CXX_FEATURE_CXX_DEFAULT_FUNCTION_TEMPLATE_ARGS 0
#endif
// cxx_defaulted_functions
#ifndef HMDB_CXX_FEATURE_CXX_DEFAULTED_FUNCTIONS
#define HMDB_CXX_FEATURE_CXX_DEFAULTED_FUNCTIONS 0
#endif
// cxx_delegating_constructors
#ifndef HMDB_CXX_FEATURE_CXX_DELEGATING_CONSTRUCTORS
#define HMDB_CXX_FEATURE_CXX_DELEGATING_CONSTRUCTORS 0
#endif
// cxx_deleted_functions
#ifndef HMDB_CXX_FEATURE_CXX_DELETED_FUNCTIONS
#define HMDB_CXX_FEATURE_CXX_DELETED_FUNCTIONS 0
#endif
// cxx_explicit_conversions
#ifndef HMDB_CXX_FEATURE_CXX_EXPLICIT_CONVERSIONS
#define HMDB_CXX_FEATURE_CXX_EXPLICIT_CONVERSIONS 0
#endif
// cxx_generalized_initializers
#ifndef HMDB_CXX_FEATURE_CXX_GENERALIZED_INITIALIZERS
#define HMDB_CXX_FEATURE_CXX_GENERALIZED_INITIALIZERS 0
#endif
// cxx_implicit_moves
#ifndef HMDB_CXX_FEATURE_CXX_IMPLICIT_MOVES
#define HMDB_CXX_FEATURE_CXX_IMPLICIT_MOVES 0
#endif
// cxx_inheriting_constructors
#ifndef HMDB_CXX_FEATURE_CXX_INHERITING_CONSTRUCTORS
#define HMDB_CXX_FEATURE_CXX_INHERITING_CONSTRUCTORS 0
#endif
// cxx_inline_namespaces
#ifndef HMDB_CXX_FEATURE_CXX_INLINE_NAMESPACES
#define HMDB_CXX_FEATURE_CXX_INLINE_NAMESPACES 0
#endif
// cxx_lambdas
#ifndef HMDB_CXX_FEATURE_CXX_LAMBDAS
#define HMDB_CXX_FEATURE_CXX_LAMBDAS 0
#endif
// cxx_local_type_template_args
#ifndef HMDB_CXX_FEATURE_CXX_LOCAL_TYPE_TEMPLATE_ARGS
#define HMDB_CXX_FEATURE_CXX_LOCAL_TYPE_TEMPLATE_ARGS 0
#endif
// cxx_noexcept
#ifndef HMDB_CXX_FEATURE_CXX_NOEXCEPT
#define HMDB_CXX_FEATURE_CXX_NOEXCEPT 0
#endif
// cxx_nonstatic_member_init
#ifndef HMDB_CXX_FEATURE_CXX_NONSTATIC_MEMBER_INIT
#define HMDB_CXX_FEATURE_CXX_NONSTATIC_MEMBER_INIT 0
#endif
// cxx_nullptr
#ifndef HMDB_CXX_FEATURE_CXX_NULLPTR
#define HMDB_CXX_FEATURE_CXX_NULLPTR 0
#endif
// cxx_override_control
#ifndef HMDB_CXX_FEATURE_CXX_OVERRIDE_CONTROL
#define HMDB_CXX_FEATURE_CXX_OVERRIDE_CONTROL 0
#endif
// cxx_reference_qualified_functions
#ifndef HMDB_CXX_FEATURE_CXX_REFERENCE_QUALIFIED_FUNCTIONS
#define HMDB_CXX_FEATURE_CXX_REFERENCE_QUALIFIED_FUNCTIONS 0
#endif
// cxx_range_for
#ifndef HMDB_CXX_FEATURE_CXX_RANGE_FOR
#define HMDB_CXX_FEATURE_CXX_RANGE_FOR 0
#endif
// cxx_raw_string_literals
#ifndef HMDB_CXX_FEATURE_CXX_RAW_STRING_LITERALS
#define HMDB_CXX_FEATURE_CXX_RAW_STRING_LITERALS 0
#endif
// cxx_rvalue_references
#ifndef HMDB_CXX_FEATURE_CXX_RVALUE_REFERENCES
#define HMDB_CXX_FEATURE_CXX_RVALUE_REFERENCES 0
#endif
// cxx_static_assert
#ifndef HMDB_CXX_FEATURE_CXX_STATIC_ASSERT
#define HMDB_CXX_FEATURE_CXX_STATIC_ASSERT 0
#endif
// cxx_auto_type
#ifndef HMDB_CXX_FEATURE_CXX_AUTO_TYPE
#define HMDB_CXX_FEATURE_CXX_AUTO_TYPE 0
#endif
// cxx_strong_enums
#ifndef HMDB_CXX_FEATURE_CXX_STRONG_ENUMS
#define HMDB_CXX_FEATURE_CXX_STRONG_ENUMS 0
#endif
// cxx_trailing_return
#ifndef HMDB_CXX_FEATURE_CXX_TRAILING_RETURN
#define HMDB_CXX_FEATURE_CXX_TRAILING_RETURN 0
#endif
// cxx_unicode_literals
#ifndef HMDB_CXX_FEATURE_CXX_UNICODE_LITERALS
#define HMDB_CXX_FEATURE_CXX_UNICODE_LITERALS 0
#endif
// cxx_unrestricted_unions
#ifndef HMDB_CXX_FEATURE_CXX_UNRESTRICTED_UNIONS
#define HMDB_CXX_FEATURE_CXX_UNRESTRICTED_UNIONS 0
#endif
// cxx_user_literals
#ifndef HMDB_CXX_FEATURE_CXX_USER_LITERALS
#define HMDB_CXX_FEATURE_CXX_USER_LITERALS 0
#endif
// cxx_variadic_templates
#ifndef HMDB_CXX_FEATURE_CXX_VARIADIC_TEMPLATES
#define HMDB_CXX_FEATURE_CXX_VARIADIC_TEMPLATES 0
#endif
/* } C++ feature */

#endif
