bin_PROGRAMS = whoson
whoson_SOURCES = main.cpp options.cpp options.hpp datetime.hpp \
    datetime.cpp output.hpp output.cpp
whoson_LDADD = ../libwhoson/libwhoson.la

##
## Build all static program:
## 
if STATIC_CLIENTS
  whoson_LDFLAGS = -static --static
endif
