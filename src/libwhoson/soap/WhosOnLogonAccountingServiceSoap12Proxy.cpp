/* WhosOnLogonAccountingServiceSoap12Proxy.cpp
   Generated by gSOAP 2.7.17 from service.h
   Copyright(C) 2000-2010, Robert van Engelen, Genivia Inc. All Rights Reserved.
   This part of the software is released under one of the following licenses:
   GPL, the gSOAP public license, or Genivia's license for commercial use.
*/

#include "WhosOnLogonAccountingServiceSoap12Proxy.h"

LogonAccountingServiceSoap12Proxy::LogonAccountingServiceSoap12Proxy()
{	LogonAccountingServiceSoap12Proxy_init(SOAP_IO_DEFAULT, SOAP_IO_DEFAULT);
}

LogonAccountingServiceSoap12Proxy::LogonAccountingServiceSoap12Proxy(const struct soap &_soap) : soap(_soap)
{ }

LogonAccountingServiceSoap12Proxy::LogonAccountingServiceSoap12Proxy(soap_mode iomode)
{	LogonAccountingServiceSoap12Proxy_init(iomode, iomode);
}

LogonAccountingServiceSoap12Proxy::LogonAccountingServiceSoap12Proxy(soap_mode imode, soap_mode omode)
{	LogonAccountingServiceSoap12Proxy_init(imode, omode);
}

void LogonAccountingServiceSoap12Proxy::LogonAccountingServiceSoap12Proxy_init(soap_mode imode, soap_mode omode)
{	soap_imode(this, imode);
	soap_omode(this, omode);
	soap_endpoint = NULL;
	static const struct Namespace namespaces[] =
{
	{"SOAP-ENV", "http://schemas.xmlsoap.org/soap/envelope/", "http://www.w3.org/*/soap-envelope", NULL},
	{"SOAP-ENC", "http://schemas.xmlsoap.org/soap/encoding/", "http://www.w3.org/*/soap-encoding", NULL},
	{"xsi", "http://www.w3.org/2001/XMLSchema-instance", "http://www.w3.org/*/XMLSchema-instance", NULL},
	{"xsd", "http://www.w3.org/2001/XMLSchema", "http://www.w3.org/*/XMLSchema", NULL},
	{"ns1", "http://it.bmc.uu.se/whoson/LogonAccountingServiceSoap", NULL, NULL},
	{"WhosOn", "http://it.bmc.uu.se/whoson", NULL, NULL},
	{"ns2", "http://it.bmc.uu.se/whoson/LogonAccountingServiceSoap12", NULL, NULL},
	{NULL, NULL, NULL, NULL}
};
	this->namespaces = namespaces;
}

LogonAccountingServiceSoap12Proxy::~LogonAccountingServiceSoap12Proxy()
{ }

void LogonAccountingServiceSoap12Proxy::destroy()
{	soap_destroy(this);
	soap_end(this);
}

void LogonAccountingServiceSoap12Proxy::soap_noheader()
{	header = NULL;
}

const SOAP_ENV__Fault *LogonAccountingServiceSoap12Proxy::soap_fault()
{	return this->fault;
}

const char *LogonAccountingServiceSoap12Proxy::soap_fault_string()
{	return *soap_faultstring(this);
}

const char *LogonAccountingServiceSoap12Proxy::soap_fault_detail()
{	return *soap_faultdetail(this);
}

int LogonAccountingServiceSoap12Proxy::soap_close_socket()
{	return soap_closesock(this);
}

void LogonAccountingServiceSoap12Proxy::soap_print_fault(FILE *fd)
{	::soap_print_fault(this, fd);
}

#ifndef WITH_LEAN
void LogonAccountingServiceSoap12Proxy::soap_stream_fault(std::ostream& os)
{	::soap_stream_fault(this, os);
}

char *LogonAccountingServiceSoap12Proxy::soap_sprint_fault(char *buf, size_t len)
{	return ::soap_sprint_fault(this, buf, len);
}
#endif

int LogonAccountingServiceSoap12Proxy::CreateLogonEvent(_WhosOn__CreateLogonEvent *WhosOn__CreateLogonEvent, _WhosOn__CreateLogonEventResponse *WhosOn__CreateLogonEventResponse)
{	struct soap *soap = this;
	struct __ns2__CreateLogonEvent soap_tmp___ns2__CreateLogonEvent;
	const char *soap_action = NULL;
	if (!soap_endpoint)
		soap_endpoint = "http://localhost/websvc/whoson2/LogonAccountingService.asmx";
	soap_action = "http://it.bmc.uu.se/whoson/CreateLogonEvent";
	soap->encodingStyle = NULL;
	soap_tmp___ns2__CreateLogonEvent.WhosOn__CreateLogonEvent = WhosOn__CreateLogonEvent;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize___ns2__CreateLogonEvent(soap, &soap_tmp___ns2__CreateLogonEvent);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put___ns2__CreateLogonEvent(soap, &soap_tmp___ns2__CreateLogonEvent, "-ns2:CreateLogonEvent", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put___ns2__CreateLogonEvent(soap, &soap_tmp___ns2__CreateLogonEvent, "-ns2:CreateLogonEvent", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!WhosOn__CreateLogonEventResponse)
		return soap_closesock(soap);
	WhosOn__CreateLogonEventResponse->soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	WhosOn__CreateLogonEventResponse->soap_get(soap, "WhosOn:CreateLogonEventResponse", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int LogonAccountingServiceSoap12Proxy::CloseLogonEvent(_WhosOn__CloseLogonEvent *WhosOn__CloseLogonEvent, _WhosOn__CloseLogonEventResponse *WhosOn__CloseLogonEventResponse)
{	struct soap *soap = this;
	struct __ns2__CloseLogonEvent soap_tmp___ns2__CloseLogonEvent;
	const char *soap_action = NULL;
	if (!soap_endpoint)
		soap_endpoint = "http://localhost/websvc/whoson2/LogonAccountingService.asmx";
	soap_action = "http://it.bmc.uu.se/whoson/CloseLogonEvent";
	soap->encodingStyle = NULL;
	soap_tmp___ns2__CloseLogonEvent.WhosOn__CloseLogonEvent = WhosOn__CloseLogonEvent;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize___ns2__CloseLogonEvent(soap, &soap_tmp___ns2__CloseLogonEvent);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put___ns2__CloseLogonEvent(soap, &soap_tmp___ns2__CloseLogonEvent, "-ns2:CloseLogonEvent", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put___ns2__CloseLogonEvent(soap, &soap_tmp___ns2__CloseLogonEvent, "-ns2:CloseLogonEvent", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!WhosOn__CloseLogonEventResponse)
		return soap_closesock(soap);
	WhosOn__CloseLogonEventResponse->soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	WhosOn__CloseLogonEventResponse->soap_get(soap, "WhosOn:CloseLogonEventResponse", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int LogonAccountingServiceSoap12Proxy::DeleteLogonEvent(_WhosOn__DeleteLogonEvent *WhosOn__DeleteLogonEvent, _WhosOn__DeleteLogonEventResponse *WhosOn__DeleteLogonEventResponse)
{	struct soap *soap = this;
	struct __ns2__DeleteLogonEvent soap_tmp___ns2__DeleteLogonEvent;
	const char *soap_action = NULL;
	if (!soap_endpoint)
		soap_endpoint = "http://localhost/websvc/whoson2/LogonAccountingService.asmx";
	soap_action = "http://it.bmc.uu.se/whoson/DeleteLogonEvent";
	soap->encodingStyle = NULL;
	soap_tmp___ns2__DeleteLogonEvent.WhosOn__DeleteLogonEvent = WhosOn__DeleteLogonEvent;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize___ns2__DeleteLogonEvent(soap, &soap_tmp___ns2__DeleteLogonEvent);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put___ns2__DeleteLogonEvent(soap, &soap_tmp___ns2__DeleteLogonEvent, "-ns2:DeleteLogonEvent", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put___ns2__DeleteLogonEvent(soap, &soap_tmp___ns2__DeleteLogonEvent, "-ns2:DeleteLogonEvent", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!WhosOn__DeleteLogonEventResponse)
		return soap_closesock(soap);
	WhosOn__DeleteLogonEventResponse->soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	WhosOn__DeleteLogonEventResponse->soap_get(soap, "WhosOn:DeleteLogonEventResponse", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int LogonAccountingServiceSoap12Proxy::FindLogonEvent(_WhosOn__FindLogonEvent *WhosOn__FindLogonEvent, _WhosOn__FindLogonEventResponse *WhosOn__FindLogonEventResponse)
{	struct soap *soap = this;
	struct __ns2__FindLogonEvent soap_tmp___ns2__FindLogonEvent;
	const char *soap_action = NULL;
	if (!soap_endpoint)
		soap_endpoint = "http://localhost/websvc/whoson2/LogonAccountingService.asmx";
	soap_action = "http://it.bmc.uu.se/whoson/FindLogonEvent";
	soap->encodingStyle = NULL;
	soap_tmp___ns2__FindLogonEvent.WhosOn__FindLogonEvent = WhosOn__FindLogonEvent;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize___ns2__FindLogonEvent(soap, &soap_tmp___ns2__FindLogonEvent);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put___ns2__FindLogonEvent(soap, &soap_tmp___ns2__FindLogonEvent, "-ns2:FindLogonEvent", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put___ns2__FindLogonEvent(soap, &soap_tmp___ns2__FindLogonEvent, "-ns2:FindLogonEvent", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!WhosOn__FindLogonEventResponse)
		return soap_closesock(soap);
	WhosOn__FindLogonEventResponse->soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	WhosOn__FindLogonEventResponse->soap_get(soap, "WhosOn:FindLogonEventResponse", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int LogonAccountingServiceSoap12Proxy::FindLogonEvents(_WhosOn__FindLogonEvents *WhosOn__FindLogonEvents, _WhosOn__FindLogonEventsResponse *WhosOn__FindLogonEventsResponse)
{	struct soap *soap = this;
	struct __ns2__FindLogonEvents soap_tmp___ns2__FindLogonEvents;
	const char *soap_action = NULL;
	if (!soap_endpoint)
		soap_endpoint = "http://localhost/websvc/whoson2/LogonAccountingService.asmx";
	soap_action = "http://it.bmc.uu.se/whoson/FindLogonEvents";
	soap->encodingStyle = NULL;
	soap_tmp___ns2__FindLogonEvents.WhosOn__FindLogonEvents = WhosOn__FindLogonEvents;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize___ns2__FindLogonEvents(soap, &soap_tmp___ns2__FindLogonEvents);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put___ns2__FindLogonEvents(soap, &soap_tmp___ns2__FindLogonEvents, "-ns2:FindLogonEvents", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put___ns2__FindLogonEvents(soap, &soap_tmp___ns2__FindLogonEvents, "-ns2:FindLogonEvents", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!WhosOn__FindLogonEventsResponse)
		return soap_closesock(soap);
	WhosOn__FindLogonEventsResponse->soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	WhosOn__FindLogonEventsResponse->soap_get(soap, "WhosOn:FindLogonEventsResponse", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}
/* End of client proxy code */