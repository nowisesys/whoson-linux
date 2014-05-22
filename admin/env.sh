#!/bin/sh
#
# Author: Anders Lövgren
# Date:   2011-12-19

# Application settings:
WHOSON_SOAP_ENDPOINT="http://localhost/whoson/"
WHOSON_DEBUG=0
WHOSON_VERBOSE=0
export WHOSON_SOAP_ENDPOINT WHOSON_DEBUG WHOSON_VERBOSE

#WHOSON_SOAP_USER="userid"
#WHOSON_SOAP_PASS="secret"
#export WHOSON_SOAP_USER WHOSON_SOAP_PASS

# For dumping SOAP request/response using tcpdump:
export TCPDUMP_OPTIONS="-nnvvlXSs 4096 port 80"
