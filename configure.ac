#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([HPCMzlib], [VERSION], [BUG-REPORT-ADDRESS])
AC_CONFIG_MACRO_DIR(m4)
m4_include([config/compiler_checks.m4])

# Checks for programs.
AC_PROG_CXX
AC_PROG_MAKE_SET

AC_MSG_CHECKING([if want developer-level debugging flags])
AC_ARG_ENABLE(debug,
  AC_HELP_STRING([Enable debug flags for compilation (default=yes)]))
if test "$enable_debug" = yes ; then
   AC_MSG_RESULT([yes])
   CXXFLAGS="-g -O0"
   CFLAGS="-g -O0"
elif test "$enable_debug" = no ; then   
   AC_MSG_RESULT([no]) 
   CXXFLAGS="-O3"
   CFLAGS="-O3"
else
   AC_MSG_RESULT([not set (implicit yes)]) 
   CXXFLAGS="-g -O0"
   CFLAGS="-g -O0"
fi 


AC_LANG_PUSH([C++])
GET_CXX_COMPILER_VENDOR(compiler_vendor)
if test "$compiler_vendor" = "gnu" ; then
  CXXFLAGS="$CXXFLAGS -Wno-delete-non-virtual-dtor -std=gnu++17"
  CPPFLAGS="$CXXFLAGS"
elif test "$compiler_vendor" = "intel" ; then
  CXXFLAGS="$CXXFLAGS -std=c++17"
  CPPFLAGS="$CXXFLAGS"
fi

PROG_CXX_CXX17_HELPER([],[have_cxx17_support])
if test "x$have_cxx17_support" = xno ; then
   AC_MSG_WARN([HPCMzLib requires a C++ 2017 (or newer) compiler.])
   AC_MSG_ERROR([Aborting.])
fi

# Checks for header files.
AC_CHECK_HEADER([zlib.h],
[],
[AC_MSG_ERROR(Couldn't find zlib.h)])

AC_CHECK_HEADER([math.h],
[],
[AC_MSG_ERROR(Couldn't find math.h)])


# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_CHECK_TYPES([ptrdiff_t])

# Checks for library functions.
AC_FUNC_ERROR_AT_LINE
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([fesetround floor pow sqrt])



dnl ==================================================
AC_MSG_CHECKING(for mzLib main directory)
AC_ARG_WITH(mzlib_dir,
 [  --with-mzlib-dir=dir            Main mzLib directory (default=$PWD)],
     mzlib_dir="${withval}", mzlib_dir="")
         if test "x$mzlib_dir" = "x" ; then
                mzlib_dir=$PWD
         fi
     AC_MSG_RESULT(${mzlib_dir})
     AC_SUBST(mzlib_dir)
dnl ==================================================

dnl ==================================================
AC_MSG_CHECKING(for mzLib lib directory)
AC_ARG_WITH(mzlib_lib_dir,
 [  --with-mzlib-lib_dir=dir            mzLib lib directory (default=mzlib_dir/lib)],
     mzlib_lib_dir="${withval}", mzlib_lib_dir="")
         if test "x$mzlib_lib_dir" = "x" ; then
                mzlib_lib_dir="$mzlib_dir"/lib
         fi
     AC_MSG_RESULT(${mzlib_lib_dir})
     AC_SUBST(mzlib_lib_dir)
dnl ==================================================


dnl ==================================================
AC_MSG_CHECKING(for libxml2)
AC_ARG_WITH(libxml2_dir,
 [  --with-libxml2-dir=dir          libxml2 directory (default=/usr/include/libxml2/)],
     libxml2_dir="${withval}", libxml2_dir="")
         if test "x$libxml2_dir" = "x" ; then
                libxml2_dir=/usr/include/libxml2
         fi
     AC_MSG_RESULT(${libxml2_dir})

     save_CXXFLAGS="$CXXFLAGS"
     save_CPPFLAGS="$CPPFLAGS"
     CXXFLAGS="$save_CXXFLAGS -I$libxml2_dir" 
     CPPFLAGS="$save_CPPFLAGS -I$libxml2_dir" 
     AC_CHECK_HEADER([libxml/xmlreader.h],
     [],
     [AC_MSG_ERROR(Couldn't find libxml/xmlreader.h)])
     CXXFLAGS="$save_CXXFLAGS"
     CPPFLAGS="$save_CPPFLAGS"
     AC_SUBST(libxml2_dir)
dnl ==================================================

dnl ==================================================
AC_MSG_CHECKING(for xsdcxx)
AC_ARG_WITH(xsdcxx_dir,
 [  --with-xsdcxx-dir=dir          xsdcxx directory (default=/usr/include)],
     xsdcxx_dir="${withval}", xsdcxx_dir="")
         if test "x$xsdcxx_dir" = "x" ; then
                xsdcxx_dir=/usr/include
         fi
     AC_MSG_RESULT(${xsdcxx_dir})

     save_CXXFLAGS="$CXXFLAGS"
     save_CPPFLAGS="$CPPFLAGS"
     CXXFLAGS="$save_CXXFLAGS -I$xsdcxx_dir" 
     CPPFLAGS="$save_CPPFLAGS -I$xsdcxx_dir" 
     AC_CHECK_HEADER([xsd/cxx/config.hxx],
     [],  
     [AC_MSG_ERROR(Couldn't find xsd/cxx/config.hxx)])

     CXXFLAGS="$save_CXXFLAGS"
     CPPFLAGS="$save_CPPFLAGS"
     AC_SUBST(xsdcxx_dir)
dnl ==================================================

AX_XERCESC

#AC_CONFIG_FILES([Makefile.defs])
AC_SUBST(CXX)
AC_SUBST(CC)
AC_SUBST(CFLAGS)
AC_SUBST(CXXFLAGS)
AC_OUTPUT("$mzlib_dir"/Makefile.defs)
