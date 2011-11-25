#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([whoson], [1.0.0], [anders.lovgren@bmc.uu.se])
AM_INIT_AUTOMAKE([whoson], [1.0.0])
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADERS([config.h])

AC_LANG(C++)

# Checks for programs.
AC_PROG_CC
AC_PROG_CXX
AC_PROG_LIBTOOL

# Test whether to build static linked client programs:
AC_ARG_ENABLE([static-clients],
  [AS_HELP_STRING(
    [--enable-static-clients],
    [Link all client programs static (default is no)])],
  [static_clients=$enableval],
  [static_clients=no])
AC_MSG_CHECKING([whether to build static clients])
AC_MSG_RESULT([${static_clients}])
AM_CONDITIONAL([STATIC_CLIENTS], [test x${static_clients} = xyes])

# Checks for libraries.

# gsoapssl   - SOAP C Web Services with SSL and ZLIB
# gsoapssl++ - SOAP C++ Web Services with SSL and ZLIB
# gsoapck    - SOAP C Web Services with Cookies Enabled
# gsoap++    - SOAP C++ Web Services
# gsoapck++  - SOAP C++ Web Services with Cookies Enabled
# gsoap      - SOAP C Web Services

pkg-config --exists gsoap++ > /dev/null
if test "$?" == "0" ; then
  whoson_have_gsoap_cxx="yes"
else 
  whoson_have_gsoap_cxx="no"
fi
AC_MSG_CHECKING([for library gsoap++])
if test "x${whoson_have_gsoap_cxx}" == "xyes" ; then
  GSOAP_LDD_FLAGS=$(pkg-config --libs gsoap++)
  GSOAP_CXX_FLAGS=$(pkg-config --cflags gsoap++)
  AC_MSG_RESULT([yes (libs: ${GSOAP_LDD_FLAGS}, cflags: ${GSOAP_CXX_FLAGS})])
  AC_DEFINE([HAVE_LIBGSOAP_CXX], [1], [Define to 1 if libgsoap++ was found])
else 
  AC_MSG_RESULT([no])
  AC_MSG_ERROR([The gSOAP Toolkit was not found. Please download and install it from http://gsoap2.sourceforge.net/])
fi

CPPFLAGS="$CPPFLAGS -I../libwhoson"
CXXFLAGS="$CXXFLAGS ${GSOAP_CXX_FLAGS}"
LDFLAGS="$LDFLAGS ${GSOAP_LDD_FLAGS}"

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile
                 src/Makefile
		 src/libwhoson/Makefile
		 src/libwhoson/soap/Makefile
		 src/whoson/Makefile
		 src/whosond/Makefile])
AC_OUTPUT
