//
//  hmdb-cxx_dialect-llvm_clang.h
//  hmdb
//
//  Created by matsuki hidenori on 3/21/13.
//
//

#ifndef hmdb_hmdb_cxx_dialect_llvm_clang_h
#define hmdb_hmdb_cxx_dialect_llvm_clang_h

#define HMDB_COMPILER_LLVM_CLANG
#define HMDB_COMPILER "LLVM_CLANG"

/* C++ feature { */
// cxx_exceptions
#ifndef HMDB_CXX_FEATURE_CXX_EXCEPTIONS
#define HMDB_CXX_FEATURE_CXX_EXCEPTIONS __has_feature(cxx_exceptions)
#endif
// cxx_rtti
#ifndef HMDB_CXX_FEATURE_CXX_RTTI
#define HMDB_CXX_FEATURE_CXX_RTTI __has_feature(cxx_rtti)
#endif
// cxx_access_control_sfinae
#ifndef HMDB_CXX_FEATURE_CXX_ACCESS_CONTROL_SFINAE
#define HMDB_CXX_FEATURE_CXX_ACCESS_CONTROL_SFINAE __has_feature(cxx_access_control_sfinae)
#endif
// cxx_alias_templates
#ifndef HMDB_CXX_FEATURE_CXX_ALIAS_TEMPLATES
#define HMDB_CXX_FEATURE_CXX_ALIAS_TEMPLATES __has_feature(cxx_alias_templates)
#endif
// cxx_alignas
#ifndef HMDB_CXX_FEATURE_CXX_ALIGNAS
#define HMDB_CXX_FEATURE_CXX_ALIGNAS __has_feature(cxx_alignas)
#endif
// cxx_attributes
#ifndef HMDB_CXX_FEATURE_CXX_ATTRIBUTES
#define HMDB_CXX_FEATURE_CXX_ATTRIBUTES __has_feature(cxx_attributes)
#endif
// cxx_constexpr
#ifndef HMDB_CXX_FEATURE_CXX_CONSTEXPR
#define HMDB_CXX_FEATURE_CXX_CONSTEXPR __has_feature(cxx_constexpr)
#endif
// cxx_decltype
#ifndef HMDB_CXX_FEATURE_CXX_DECLTYPE
#define HMDB_CXX_FEATURE_CXX_DECLTYPE __has_feature(cxx_decltype)
#endif
// cxx_default_function_template_args
#ifndef HMDB_CXX_FEATURE_CXX_DEFAULT_FUNCTION_TEMPLATE_ARGS
#define HMDB_CXX_FEATURE_CXX_DEFAULT_FUNCTION_TEMPLATE_ARGS __has_feature(cxx_default_function_template_args)
#endif
// cxx_defaulted_functions
#ifndef HMDB_CXX_FEATURE_CXX_DEFAULTED_FUNCTIONS
#define HMDB_CXX_FEATURE_CXX_DEFAULTED_FUNCTIONS __has_feature(cxx_defaulted_functions)
#endif
// cxx_delegating_constructors
#ifndef HMDB_CXX_FEATURE_CXX_DELEGATING_CONSTRUCTORS
#define HMDB_CXX_FEATURE_CXX_DELEGATING_CONSTRUCTORS __has_feature(cxx_delegating_constructors)
#endif
// cxx_deleted_functions
#ifndef HMDB_CXX_FEATURE_CXX_DELETED_FUNCTIONS
#define HMDB_CXX_FEATURE_CXX_DELETED_FUNCTIONS __has_feature(cxx_deleted_functions)
#endif
// cxx_explicit_conversions
#ifndef HMDB_CXX_FEATURE_CXX_EXPLICIT_CONVERSIONS
#define HMDB_CXX_FEATURE_CXX_EXPLICIT_CONVERSIONS __has_feature(cxx_explicit_conversions)
#endif
// cxx_generalized_initializers
#ifndef HMDB_CXX_FEATURE_CXX_GENERALIZED_INITIALIZERS
#define HMDB_CXX_FEATURE_CXX_GENERALIZED_INITIALIZERS __has_feature(cxx_generalized_initializers)
#endif
// cxx_implicit_moves
#ifndef HMDB_CXX_FEATURE_CXX_IMPLICIT_MOVES
#define HMDB_CXX_FEATURE_CXX_IMPLICIT_MOVES __has_feature(cxx_implicit_moves)
#endif
// cxx_inheriting_constructors
#ifndef HMDB_CXX_FEATURE_CXX_INHERITING_CONSTRUCTORS
#define HMDB_CXX_FEATURE_CXX_INHERITING_CONSTRUCTORS __has_feature(cxx_inheriting_constructors)
#endif
// cxx_inline_namespaces
#ifndef HMDB_CXX_FEATURE_CXX_INLINE_NAMESPACES
#define HMDB_CXX_FEATURE_CXX_INLINE_NAMESPACES __has_feature(cxx_inline_namespaces)
#endif
// cxx_lambdas
#ifndef HMDB_CXX_FEATURE_CXX_LAMBDAS
#define HMDB_CXX_FEATURE_CXX_LAMBDAS __has_feature(cxx_lambdas)
#endif
// cxx_local_type_template_args
#ifndef HMDB_CXX_FEATURE_CXX_LOCAL_TYPE_TEMPLATE_ARGS
#define HMDB_CXX_FEATURE_CXX_LOCAL_TYPE_TEMPLATE_ARGS __has_feature(cxx_local_type_template_args)
#endif
// cxx_noexcept
#ifndef HMDB_CXX_FEATURE_CXX_NOEXCEPT
#define HMDB_CXX_FEATURE_CXX_NOEXCEPT __has_feature(cxx_noexcept)
#endif
// cxx_nonstatic_member_init
#ifndef HMDB_CXX_FEATURE_CXX_NONSTATIC_MEMBER_INIT
#define HMDB_CXX_FEATURE_CXX_NONSTATIC_MEMBER_INIT __has_feature(cxx_nonstatic_member_init)
#endif
// cxx_nullptr
#ifndef HMDB_CXX_FEATURE_CXX_NULLPTR
#define HMDB_CXX_FEATURE_CXX_NULLPTR __has_feature(cxx_nullptr)
#endif
// cxx_override_control
#ifndef HMDB_CXX_FEATURE_CXX_OVERRIDE_CONTROL
#define HMDB_CXX_FEATURE_CXX_OVERRIDE_CONTROL __has_feature(cxx_override_control)
#endif
// cxx_reference_qualified_functions
#ifndef HMDB_CXX_FEATURE_CXX_REFERENCE_QUALIFIED_FUNCTIONS
#define HMDB_CXX_FEATURE_CXX_REFERENCE_QUALIFIED_FUNCTIONS __has_feature(cxx_reference_qualified_functions)
#endif
// cxx_range_for
#ifndef HMDB_CXX_FEATURE_CXX_RANGE_FOR
#define HMDB_CXX_FEATURE_CXX_RANGE_FOR __has_feature(cxx_range_for)
#endif
// cxx_raw_string_literals
#ifndef HMDB_CXX_FEATURE_CXX_RAW_STRING_LITERALS
#define HMDB_CXX_FEATURE_CXX_RAW_STRING_LITERALS __has_feature(cxx_raw_string_literals)
#endif
// cxx_rvalue_references
#ifndef HMDB_CXX_FEATURE_CXX_RVALUE_REFERENCES
#define HMDB_CXX_FEATURE_CXX_RVALUE_REFERENCES __has_feature(cxx_rvalue_references)
#endif
// cxx_static_assert
#ifndef HMDB_CXX_FEATURE_CXX_STATIC_ASSERT
#define HMDB_CXX_FEATURE_CXX_STATIC_ASSERT __has_feature(cxx_static_assert)
#endif
// cxx_auto_type
#ifndef HMDB_CXX_FEATURE_CXX_AUTO_TYPE
#define HMDB_CXX_FEATURE_CXX_AUTO_TYPE __has_feature(cxx_auto_type)
#endif
// cxx_strong_enums
#ifndef HMDB_CXX_FEATURE_CXX_STRONG_ENUMS
#define HMDB_CXX_FEATURE_CXX_STRONG_ENUMS __has_feature(cxx_strong_enums)
#endif
// cxx_trailing_return
#ifndef HMDB_CXX_FEATURE_CXX_TRAILING_RETURN
#define HMDB_CXX_FEATURE_CXX_TRAILING_RETURN __has_feature(cxx_trailing_return)
#endif
// cxx_unicode_literals
#ifndef HMDB_CXX_FEATURE_CXX_UNICODE_LITERALS
#define HMDB_CXX_FEATURE_CXX_UNICODE_LITERALS __has_feature(cxx_unicode_literals)
#endif
// cxx_unrestricted_unions
#ifndef HMDB_CXX_FEATURE_CXX_UNRESTRICTED_UNIONS
#define HMDB_CXX_FEATURE_CXX_UNRESTRICTED_UNIONS __has_feature(cxx_unrestricted_unions)
#endif
// cxx_user_literals
#ifndef HMDB_CXX_FEATURE_CXX_USER_LITERALS
#define HMDB_CXX_FEATURE_CXX_USER_LITERALS __has_feature(cxx_user_literals)
#endif
// cxx_variadic_templates
#ifndef HMDB_CXX_FEATURE_CXX_VARIADIC_TEMPLATES
#define HMDB_CXX_FEATURE_CXX_VARIADIC_TEMPLATES __has_feature(cxx_variadic_templates)
#endif
/* } C++ feature */

#endif
