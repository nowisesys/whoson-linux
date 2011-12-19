#!/bin/sh
#
# Author: Anders Lövgren
# Date:   2011-12-19

# Application settings:
WHOSON_SOAP_ENDPOINT="http://localhost/websvc/whoson2/LogonAccountingService.asmx"
WHOSON_DEBUG=0
WHOSON_VERBOSE=0
export WHOSON_SOAP_ENDPOINT WHOSON_DEBUG WHOSON_VERBOSE

# For dumping SOAP request/response using tcpdump:
export TCPDUMP_OPTIONS="-nnvvlXSs 4096 port 80"
