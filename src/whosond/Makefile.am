sbin_PROGRAMS = whosond
whosond_SOURCES = main.cpp
whosond_LDADD = ../libwhoson/libwhoson.la

##
## Build all static program:
## 
if STATIC_CLIENTS
  whosond_LDFLAGS = -static --static
endif
