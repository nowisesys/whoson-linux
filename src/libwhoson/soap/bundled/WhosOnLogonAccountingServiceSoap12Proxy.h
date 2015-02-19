/* WhosOnLogonAccountingServiceSoap12Proxy.h
   Generated by gSOAP 2.8.19 from service.h

Copyright(C) 2000-2014, Robert van Engelen, Genivia Inc. All Rights Reserved.
The generated code is released under one of the following licenses:
GPL or Genivia's license for commercial use.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
*/

#ifndef WhosOnLogonAccountingServiceSoap12Proxy_H
#define WhosOnLogonAccountingServiceSoap12Proxy_H
#include "WhosOnH.h"

class SOAP_CMAC LogonAccountingServiceSoap12Proxy : public soap
{ public:
	/// Endpoint URL of service 'LogonAccountingServiceSoap12Proxy' (change as needed)
	const char *soap_endpoint;
	/// Variables globally declared in service.h (non-static)
	/// Constructor
	LogonAccountingServiceSoap12Proxy();
	/// Construct from another engine state
	LogonAccountingServiceSoap12Proxy(const struct soap&);
	/// Constructor with endpoint URL
	LogonAccountingServiceSoap12Proxy(const char *url);
	/// Constructor with engine input+output mode control
	LogonAccountingServiceSoap12Proxy(soap_mode iomode);
	/// Constructor with URL and input+output mode control
	LogonAccountingServiceSoap12Proxy(const char *url, soap_mode iomode);
	/// Constructor with engine input and output mode control
	LogonAccountingServiceSoap12Proxy(soap_mode imode, soap_mode omode);
	/// Destructor frees deserialized data
	virtual	~LogonAccountingServiceSoap12Proxy();
	/// Initializer used by constructors
	virtual	void LogonAccountingServiceSoap12Proxy_init(soap_mode imode, soap_mode omode);
	/// Delete all deserialized data (with soap_destroy and soap_end)
	virtual	void destroy();
	/// Delete all deserialized data and reset to default
	virtual	void reset();
	/// Disables and removes SOAP Header from message
	virtual	void soap_noheader();
	/// Get SOAP Header structure (NULL when absent)
	virtual	const SOAP_ENV__Header *soap_header();
	/// Get SOAP Fault structure (NULL when absent)
	virtual	const SOAP_ENV__Fault *soap_fault();
	/// Get SOAP Fault string (NULL when absent)
	virtual	const char *soap_fault_string();
	/// Get SOAP Fault detail as string (NULL when absent)
	virtual	const char *soap_fault_detail();
	/// Close connection (normally automatic, except for send_X ops)
	virtual	int soap_close_socket();
	/// Force close connection (can kill a thread blocked on IO)
	virtual	int soap_force_close_socket();
	/// Print fault
	virtual	void soap_print_fault(FILE*);
#ifndef WITH_LEAN
	/// Print fault to stream
#ifndef WITH_COMPAT
	virtual	void soap_stream_fault(std::ostream&);
#endif

	/// Put fault into buffer
	virtual	char *soap_sprint_fault(char *buf, size_t len);
#endif

	/// Web service operation 'CreateLogonEvent' (returns error code or SOAP_OK)
	virtual	int CreateLogonEvent(_WhosOn__CreateLogonEvent *WhosOn__CreateLogonEvent, _WhosOn__CreateLogonEventResponse *WhosOn__CreateLogonEventResponse) { return this->CreateLogonEvent(NULL, NULL, WhosOn__CreateLogonEvent, WhosOn__CreateLogonEventResponse); }
	virtual	int CreateLogonEvent(const char *endpoint, const char *soap_action, _WhosOn__CreateLogonEvent *WhosOn__CreateLogonEvent, _WhosOn__CreateLogonEventResponse *WhosOn__CreateLogonEventResponse);

	/// Web service operation 'CloseLogonEvent' (returns error code or SOAP_OK)
	virtual	int CloseLogonEvent(_WhosOn__CloseLogonEvent *WhosOn__CloseLogonEvent, _WhosOn__CloseLogonEventResponse *WhosOn__CloseLogonEventResponse) { return this->CloseLogonEvent(NULL, NULL, WhosOn__CloseLogonEvent, WhosOn__CloseLogonEventResponse); }
	virtual	int CloseLogonEvent(const char *endpoint, const char *soap_action, _WhosOn__CloseLogonEvent *WhosOn__CloseLogonEvent, _WhosOn__CloseLogonEventResponse *WhosOn__CloseLogonEventResponse);

	/// Web service operation 'DeleteLogonEvent' (returns error code or SOAP_OK)
	virtual	int DeleteLogonEvent(_WhosOn__DeleteLogonEvent *WhosOn__DeleteLogonEvent, _WhosOn__DeleteLogonEventResponse *WhosOn__DeleteLogonEventResponse) { return this->DeleteLogonEvent(NULL, NULL, WhosOn__DeleteLogonEvent, WhosOn__DeleteLogonEventResponse); }
	virtual	int DeleteLogonEvent(const char *endpoint, const char *soap_action, _WhosOn__DeleteLogonEvent *WhosOn__DeleteLogonEvent, _WhosOn__DeleteLogonEventResponse *WhosOn__DeleteLogonEventResponse);

	/// Web service operation 'FindLogonEvent' (returns error code or SOAP_OK)
	virtual	int FindLogonEvent(_WhosOn__FindLogonEvent *WhosOn__FindLogonEvent, _WhosOn__FindLogonEventResponse *WhosOn__FindLogonEventResponse) { return this->FindLogonEvent(NULL, NULL, WhosOn__FindLogonEvent, WhosOn__FindLogonEventResponse); }
	virtual	int FindLogonEvent(const char *endpoint, const char *soap_action, _WhosOn__FindLogonEvent *WhosOn__FindLogonEvent, _WhosOn__FindLogonEventResponse *WhosOn__FindLogonEventResponse);

	/// Web service operation 'FindLogonEvents' (returns error code or SOAP_OK)
	virtual	int FindLogonEvents(_WhosOn__FindLogonEvents *WhosOn__FindLogonEvents, _WhosOn__FindLogonEventsResponse *WhosOn__FindLogonEventsResponse) { return this->FindLogonEvents(NULL, NULL, WhosOn__FindLogonEvents, WhosOn__FindLogonEventsResponse); }
	virtual	int FindLogonEvents(const char *endpoint, const char *soap_action, _WhosOn__FindLogonEvents *WhosOn__FindLogonEvents, _WhosOn__FindLogonEventsResponse *WhosOn__FindLogonEventsResponse);
};
#endif
