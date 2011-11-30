noinst_PROGRAMS = network
network_SOURCES = ../network.cpp

LIBS = -lwhoson

AM_CPPFLAGS = -I../../..
AM_CXXFLAGS = -DHAVE_CONFIG_H=1 -D__LIBWHOSON_HAS_MAIN__=1
AM_LDFLAGS  = -L../.libs -Wl,-rpath=../.libs
