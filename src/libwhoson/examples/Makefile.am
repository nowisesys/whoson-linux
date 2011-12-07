noinst_PROGRAMS = network account getip 
network_SOURCES = ../network.cpp
account_SOURCES = ../account.cpp
getip_SOURCES = getip.cpp

LIBS = -lwhoson

AM_CPPFLAGS = -I../../..
AM_CXXFLAGS = -DHAVE_CONFIG_H=1 -D__LIBWHOSON_HAS_MAIN__=1
AM_LDFLAGS  = -L../.libs @EXAMPLE_LDFLAGS@
