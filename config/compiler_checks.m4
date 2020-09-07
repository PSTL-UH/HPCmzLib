# The m4 macros are strongly based on the Open MPI configure logic. The macros
# have been adapted to the requirements of this project.

# GET_CXX_COMPILER_VENDOR(VENDOR_VARIABLE)
# ---------------------------------------
# Set shell variable VENDOR_VARIABLE to the name of the compiler
# vendor for the current C++ compiler.
#
AC_DEFUN([GET_CXX_COMPILER_VENDOR], [
    AC_REQUIRE([AC_PROG_CXX])

    AC_CACHE_CHECK([for the C++ compiler vendor],
                   [_cv_cxx_compiler_vendor],
                   [AC_LANG_PUSH(C++)
                   CHECK_COMPILER_VENDOR([_cv_cxx_compiler_vendor])
                   AC_LANG_POP(C++)])

    $1="$_cv_cxx_compiler_vendor"
])


# OPAL_IFDEF_IFELSE(symbol, [action-if-defined],
#                   [action-if-not-defined])
# ----------------------------------------------
# Run compiler to determine if preprocessor symbol "symbol" is
# defined by the compiler.
AC_DEFUN([OPAL_IFDEF_IFELSE], [
    AC_COMPILE_IFELSE([AC_LANG_DEFINES_PROVIDED
#ifndef $1
#error "symbol $1 not defined"
choke me
#endif], [$2], [$3])])

# OPAL_IF_IFELSE(symbol, [action-if-defined],
#                [action-if-not-defined])
# ----------------------------------------------
# Run compiler to determine if preprocessor symbol "symbol" is
# defined by the compiler.
AC_DEFUN([OPAL_IF_IFELSE], [
    AC_COMPILE_IFELSE([AC_LANG_DEFINES_PROVIDED
#if !( $1 )
#error "condition $1 not met"
choke me
#endif], [$2], [$3])])


AC_DEFUN([CHECK_COMPILER_VENDOR], [
    compiler_vendor_result="unknown"

    # GNU is probably the most common, so check that one as soon as
    # possible.  Intel and PGI18 pretends to be GNU, so need to check Intel
    # and PGI before checking for GNU.

    # Intel
     AS_IF([test "$compiler_vendor_result" = "unknown"],
           [OPAL_IF_IFELSE([defined(__INTEL_COMPILER) || defined(__ICC)],
           [compiler_vendor_result="intel"])])

    # Portland Group
     AS_IF([test "$compiler_vendor_result" = "unknown"],
           [OPAL_IFDEF_IFELSE([__PGI],
           [compiler_vendor_result="portland group"])])

    # GNU
    AS_IF([test "$compiler_vendor_result" = "unknown"],
          [OPAL_IFDEF_IFELSE([__GNUC__],
          [compiler_vendor_result="gnu"])])

    $1="$compiler_vendor_result"
])

AC_DEFUN([CXX_HELPER],[
    AC_MSG_CHECKING([$1])

    AC_LINK_IFELSE([AC_LANG_PROGRAM([$3],[$4])],
                       [$2=1
                        cxx_helper_result=yes],
                       [$2=0
                        cxx_helper_result=no])

    AC_MSG_RESULT([$cxx_helper_result])
])


AC_DEFUN([PROG_CXX_CXX17_HELPER],[

    prog_cxx_cxx17_helper_CXXFLAGS_save=$CXXFLAGS
        CXXFLAGS="$CXXFLAGS $1"


    CXX_HELPER([if $CXX $1 supports C++ std::optional], [prog_cxx_cxx17_helper__optional],
                       [[#include <optional>]],[std::optional<int> m = std::make_optional(1);])

    CXX_HELPER([if $CXX $1 supports C++ std::filesystem], [prog_cxx_cxx17_helper__filesystem],
                       [[#include <filesystem>]],[])

    #add other features as required

    AS_IF([test $prog_cxx_cxx17_helper__optional -eq 1 && test $prog_cxx_cxx17_helper__filesystem -eq 1],
           [$2="yes"],
           [$2="no"])

    CXXFLAGS=$prog_cxx_cxx17_helper_CXXFLAGS_save
])
