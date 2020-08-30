#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([Mzlib-C++], [VERSION], [BUG-REPORT-ADDRESS])
AC_CONFIG_MACRO_DIR(m4)

# Checks for programs.
AC_PROG_CXX
AX_CXX_COMPILE_STDCXX_17(ext, mandatory)
AX_CXXFLAGS_WARN_ALL
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
AX_CHECK_COMPILE_FLAG([-Wno-delete-non-virtual-dtor], [CXXFLAGS="$CXXFLAGS -Wno-delete-non-virtual-dtor"],,[$ERROR_ON_UNKNOWN_OPTIONS])

# Checks for libraries.

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

AX_XERCESC
AX_XSDCXX


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
AC_MSG_CHECKING(for cereal)
AC_ARG_WITH(cereal_dir,
 [  --with-cereal-dir=dir          cereal directory (default=/usr/include/cereal/)],
     cereal_dir="${withval}", cereal_dir="")
         if test "x$cereal_dir" = "x" ; then
                cereal_dir=/usr/include/cereal
         fi
     AC_MSG_RESULT(${cereal_dir})

     save_CXXFLAGS="$CXXFLAGS"
     save_CPPFLAGS="$CPPFLAGS"
     CXXFLAGS="$save_CXXFLAGS -I$cereal_dir" 
     CPPFLAGS="$save_CPPFLAGS -I$cereal_dir" 
     AC_CHECK_HEADER([cereal/cereal.hpp],
     [],  
     [AC_MSG_ERROR(Couldn't find cereal.hpp)])

     CXXFLAGS="$save_CXXFLAGS"
     CPPFLAGS="$save_CPPFLAGS"
     AC_SUBST(cereal_dir)
dnl ==================================================


#AC_CONFIG_FILES([Makefile.defs])
AC_SUBST(CXX)
AC_SUBST(CC)
AC_SUBST(CFLAGS)
AC_SUBST(CXXFLAGS)
AC_OUTPUT(Makefile.defs)
