#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([whoson], [1.0.0], [anders.lovgren@bmc.uu.se])
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADERS([config.h])

AC_LANG(C++)
AC_CONFIG_MACRO_DIR([m4])

# Checks for programs.
AC_PROG_CXX
AC_PROG_AWK
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_LIBTOOL
PKG_PROG_PKG_CONFIG

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

# Test whether to build examples:
AC_ARG_ENABLE([examples],
  [AS_HELP_STRING(
    [--enable-examples],
    [Build example programs])],
  [build_examples=$enableval],
  [build_examples=yes])
AC_MSG_CHECKING([whether to build examples])
AC_MSG_RESULT([${build_examples}])
AM_CONDITIONAL([BUILD_EXAMPLES], [test x${build_examples} = xyes])

# Checks for libraries.

## ------------------------------------
##  gSOAP
## ------------------------------------

# gsoapssl   - SOAP C Web Services with SSL and ZLIB
# gsoapssl++ - SOAP C++ Web Services with SSL and ZLIB
# gsoapck    - SOAP C Web Services with Cookies Enabled
# gsoap++    - SOAP C++ Web Services
# gsoapck++  - SOAP C++ Web Services with Cookies Enabled
# gsoap      - SOAP C Web Services

# Set to yes if libsoap++ is found:
whoson_have_gsoap_cxx="no"

PKG_CHECK_EXISTS([gsoap++],
  [PKG_CHECK_MODULES(
    [gSOAP], [gsoap++],
    [
      GSOAP_LIBS="${pkg_cv_gSOAP_LIBS}"
      GSOAP_CXXFLAGS="${pkg_cv_gSOAP_CFLAGS}"
      whoson_have_gsoap_cxx="yes"
    ],
    [ whoson_have_gsoap_cxx="no" ]
    )]
)

if test "x${whoson_have_gsoap_cxx}" = "xno" ; then
  # Using the standard AC_CHECK_LIB() won't work.
  for d in /usr /usr/local /usr/local/gsoap /opt /opt/gsoap; do
    if test -e "$d/lib/libgsoap++.a" ; then
      GSOAP_LIBS="-L$d/lib -lgsoap++"
      whoson_have_gsoap_cxx="yes"
    fi
    if test -e "$d/include/stdsoap2.h" ; then
      GSOAP_CXXFLAGS="-I$d/include"
    fi
  done
fi

AC_MSG_CHECKING([whether gSOAP was found])
if test "x${whoson_have_gsoap_cxx}" == "xyes" ; then
  AC_MSG_RESULT([yes, (libs: ${GSOAP_LIBS}, cxxflags: ${GSOAP_CXXFLAGS})])
  AC_DEFINE([HAVE_LIBGSOAP_CXX], [1], [Define to 1 if libgsoap++ was found])
else 
  AC_MSG_RESULT([no])
  AC_MSG_ERROR([The gSOAP Toolkit was not found. Please download and install it from http://gsoap2.sourceforge.net/])
fi

## ------------------------------------
##  Samba (winbind)
## ------------------------------------
AC_CHECK_LIB([wbclient], [wb_context_init])

# Checks for header files.
AC_CHECK_HEADERS([arpa/inet.h inttypes.h netinet/in.h stdint.h stdlib.h string.h sys/ioctl.h sys/socket.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_SIZE_T
AC_TYPE_UINT32_T

# Checks for library functions.
AC_FUNC_MKTIME
AC_CHECK_FUNCS([socket stime strerror strpbrk])

# Append pre-processor, C++ compiler and linker flags:
CPPFLAGS="$CPPFLAGS -I../libwhoson"
CXXFLAGS="$CXXFLAGS ${GSOAP_CXXFLAGS}"
LIBS="$LIBS ${GSOAP_LIBS}"

AC_CONFIG_FILES([Makefile
                 src/Makefile
		 src/libwhoson/Makefile
		 src/libwhoson/soap/Makefile
		 src/libwhoson/examples/Makefile
		 src/whoson/Makefile
		 src/whosond/Makefile])
AC_OUTPUT
