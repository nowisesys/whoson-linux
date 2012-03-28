#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.61])
AC_INIT([whoson], [1.1.0], [anders.lovgren@bmc.uu.se])
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADERS([config.h])
AC_CANONICAL_HOST

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

dnl Platform-specific Makefile setup
EXAMPLE_LDFLAGS=
case "${host}" in
 *-*-linux*) EXAMPLE_LDFLAGS="-Wl,-rpath=../.libs" ;;
esac
AC_SUBST([EXAMPLE_LDFLAGS])

# Test whether to build static linked client programs:
AC_ARG_ENABLE([static-all],
  [AS_HELP_STRING(
    [--enable-static-all],
    [Link all libraries and clients static (no)])],
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

with_krb5=yes
AC_ARG_WITH([krb5],
  [AS_HELP_STRING(
    [--with-krb5],
    [Enable Kerberos v5 (yes)])],
  [with_krb5=$withval],
  [with_krb5=${with_krb5}])

AC_ARG_WITH([gsoap],
  [AS_HELP_STRING(
    [--with-gsoap=PATH],
    [Check for gSOAP installation in PATH])],
  [with_gsoap=$withval])

AC_ARG_WITH([gsoap],
  [AS_HELP_STRING(
    [--with-gsoap-include=PATH],
    [Check for gSOAP header files in PATH])],
  [with_gsoap_inc=$withval])

AC_ARG_WITH([gsoap],
  [AS_HELP_STRING(
    [--with-gsoap-libs=PATH],
    [Check for gSOAP libraries in PATH])],
  [with_gsoap_lib=$withval])

# Disable wbclient by default if --enable-static-all:
with_wbclient=yes
if test x${static_clients} = xyes; then
  with_wbclient=no
fi
AC_ARG_WITH([wbclient],
  [AS_HELP_STRING(
    [--with-wbclient],
    [Check for wbclient library from SAMBA (yes)])],
  [with_wbclient=$withval],
  [with_wbclient=${with_wbclient}])
  

# Strips leading/trailing whitespace:
function whoson_trim() { echo $1; }


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
    [gsoap], [gsoap++],
    [
      GSOAP_LIBS="$(whoson_trim ${pkg_cv_gsoap_LIBS})"
      GSOAP_CXXFLAGS="$(whoson_trim ${pkg_cv_gsoap_CFLAGS})"
      whoson_have_gsoap_cxx="yes"
    ],
    [ whoson_have_gsoap_cxx="no" ]
    )]
)

#
# Try to find library and header in --with-gsoap-xxx:
# 
if test -n "x${with_gsoap_lib}" ; then
  if test -e "${with_gsoap_lib}/libgsoap++.a" ; then
    GSOAP_LIBS="-L${with_gsoap_lib} -lgsoap++"
    whoson_have_gsoap_cxx="yes"
  fi
fi
if test -n "x${with_gsoap_inc}" ; then
  if test -e "${with_gsoap_inc}/stdsoap2.h" ; then
    GSOAP_CXXFLAGS="-I${with_gsoap_inc}"
  fi
fi

if test "x${whoson_have_gsoap_cxx}" = "xno" -o "${with_gsoap}" != "" ; then
  # Using the standard AC_CHECK_LIB() won't work.
  for d in ${with_gsoap} /usr /usr/local /usr/local/gsoap /opt /opt/gsoap; do
    if test -e "$d/lib/libgsoap++.a" ; then
      GSOAP_LIBS="-L$d/lib -lgsoap++"
      whoson_have_gsoap_cxx="yes"
    fi
    if test -e "$d/include/stdsoap2.h" ; then
      GSOAP_CXXFLAGS="-I$d/include"
    fi
  done
fi

if test "${with_gsoap}" != ""; then
  AC_SUBST(GSOAPHOME, ${with_gsoap})
else
  AC_SUBST(GSOAPHOME, /usr/share/gsoap)
fi

AC_MSG_CHECKING([how to link gsoap])
if test "x${whoson_have_gsoap_cxx}" == "xyes" ; then
  AC_MSG_RESULT([libs: ${GSOAP_LIBS}, cxxflags: ${GSOAP_CXXFLAGS}])
  AC_DEFINE([HAVE_LIBGSOAP_CXX], [1], [Define to 1 if libgsoap++ was found])
else 
  AC_MSG_RESULT([missing])
  AC_MSG_ERROR([The gSOAP Toolkit was not found. Please download and install it from http://gsoap2.sourceforge.net/])
fi

## ------------------------------------
##  Samba (winbind)
## ------------------------------------
if test "x${with_wbclient}" = "xyes"; then
  AC_CHECK_LIB([wbclient], [wb_context_init])
fi

## ------------------------------------
##  Kerberos V5
## ------------------------------------
if test "x${with_krb5}" = "xyes"; then
  AC_CHECK_LIB([krb5], [krb5_init_context])
  AC_CHECK_FUNC([com_err], 
                [AC_DEFINE([HAVE_COM_ERR], [1],
		           [Define to 1 if you have the 'com_err' function.])
		])
  # if test x${ac_cv_func_com_err} = xno ; then
  #   AC_CHECK_LIB([com_err], [com_err])
  # fi
fi

# Checks for header files.
AC_CHECK_HEADERS([arpa/inet.h inttypes.h netinet/in.h stdint.h stdlib.h string.h sys/ioctl.h sys/socket.h unistd.h])
if test "x${with_krb5}" = "xyes"; then
  AC_CHECK_HEADERS([krb5.h com_err.h])
fi

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
		 src/whosond/Makefile
		 docs/Makefile])
AC_OUTPUT
