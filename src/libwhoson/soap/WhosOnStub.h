/* WhosOnStub.h
   Generated by gSOAP 2.7.17 from service.h
   Copyright(C) 2000-2010, Robert van Engelen, Genivia Inc. All Rights Reserved.
   This part of the software is released under one of the following licenses:
   GPL, the gSOAP public license, or Genivia's license for commercial use.
*/

#ifndef WhosOnStub_H
#define WhosOnStub_H
#include <vector>
#define SOAP_NAMESPACE_OF_WhosOn	"http://it.bmc.uu.se/whoson"
#include "stdsoap2.h"

/******************************************************************************\
 *                                                                            *
 * Enumerations                                                               *
 *                                                                            *
\******************************************************************************/


#ifndef SOAP_TYPE_WhosOn__LogonEventMatch
#define SOAP_TYPE_WhosOn__LogonEventMatch (20)
/* WhosOn:LogonEventMatch */
enum WhosOn__LogonEventMatch {Before = 0, Between = 1, After = 2, Exact = 3, Active = 4, Closed = 5};
#endif

/******************************************************************************\
 *                                                                            *
 * Types with Custom Serializers                                              *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Classes and Structs                                                        *
 *                                                                            *
\******************************************************************************/


#if 0 /* volatile type: do not declare here, declared elsewhere */

#endif

#if 0 /* volatile type: do not declare here, declared elsewhere */

#endif

#ifndef SOAP_TYPE_WhosOn__LogonEvent
#define SOAP_TYPE_WhosOn__LogonEvent (8)
/* WhosOn:LogonEvent */
class SOAP_CMAC WhosOn__LogonEvent
{
public:
	int EventID;	/* required element of type xsd:int */
	std::string *Username;	/* optional element of type xsd:string */
	std::string *Domain;	/* optional element of type xsd:string */
	std::string *HwAddress;	/* optional element of type xsd:string */
	std::string *IpAddress;	/* optional element of type xsd:string */
	std::string *Hostname;	/* optional element of type xsd:string */
	std::string *Workstation;	/* optional element of type xsd:string */
	time_t StartTime;	/* required element of type xsd:dateTime */
	time_t EndTime;	/* required element of type xsd:dateTime */
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 8; } /* = unique id SOAP_TYPE_WhosOn__LogonEvent */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         WhosOn__LogonEvent(): Username(NULL), Domain(NULL), HwAddress(NULL), IpAddress(NULL), Hostname(NULL), Workstation(NULL), soap(NULL) { WhosOn__LogonEvent::soap_default(NULL); }
	virtual ~WhosOn__LogonEvent() { }
};
#endif

#ifndef SOAP_TYPE_WhosOn__ArrayOfLogonEvent
#define SOAP_TYPE_WhosOn__ArrayOfLogonEvent (9)
/* WhosOn:ArrayOfLogonEvent */
class SOAP_CMAC WhosOn__ArrayOfLogonEvent
{
public:
	std::vector<WhosOn__LogonEvent * >LogonEvent;	/* optional element of type WhosOn:LogonEvent */
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 9; } /* = unique id SOAP_TYPE_WhosOn__ArrayOfLogonEvent */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         WhosOn__ArrayOfLogonEvent(): soap(NULL) { WhosOn__ArrayOfLogonEvent::soap_default(NULL); }
	virtual ~WhosOn__ArrayOfLogonEvent() { }
};
#endif

#ifndef SOAP_TYPE__WhosOn__CreateLogonEvent
#define SOAP_TYPE__WhosOn__CreateLogonEvent (10)
/* WhosOn:CreateLogonEvent */
class SOAP_CMAC _WhosOn__CreateLogonEvent
{
public:
	std::string *user;	/* optional element of type xsd:string */
	std::string *domain;	/* optional element of type xsd:string */
	std::string *computer;	/* optional element of type xsd:string */
	std::string *hwaddr;	/* optional element of type xsd:string */
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 10; } /* = unique id SOAP_TYPE__WhosOn__CreateLogonEvent */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         _WhosOn__CreateLogonEvent(): user(NULL), domain(NULL), computer(NULL), hwaddr(NULL), soap(NULL) { _WhosOn__CreateLogonEvent::soap_default(NULL); }
	virtual ~_WhosOn__CreateLogonEvent() { }
};
#endif

#ifndef SOAP_TYPE__WhosOn__CreateLogonEventResponse
#define SOAP_TYPE__WhosOn__CreateLogonEventResponse (11)
/* WhosOn:CreateLogonEventResponse */
class SOAP_CMAC _WhosOn__CreateLogonEventResponse
{
public:
	int CreateLogonEventResult;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:int */
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 11; } /* = unique id SOAP_TYPE__WhosOn__CreateLogonEventResponse */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         _WhosOn__CreateLogonEventResponse(): soap(NULL) { _WhosOn__CreateLogonEventResponse::soap_default(NULL); }
	virtual ~_WhosOn__CreateLogonEventResponse() { }
};
#endif

#ifndef SOAP_TYPE__WhosOn__CloseLogonEvent
#define SOAP_TYPE__WhosOn__CloseLogonEvent (12)
/* WhosOn:CloseLogonEvent */
class SOAP_CMAC _WhosOn__CloseLogonEvent
{
public:
	int eventID;	/* required element of type xsd:int */
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 12; } /* = unique id SOAP_TYPE__WhosOn__CloseLogonEvent */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         _WhosOn__CloseLogonEvent(): soap(NULL) { _WhosOn__CloseLogonEvent::soap_default(NULL); }
	virtual ~_WhosOn__CloseLogonEvent() { }
};
#endif

#ifndef SOAP_TYPE__WhosOn__CloseLogonEventResponse
#define SOAP_TYPE__WhosOn__CloseLogonEventResponse (13)
/* WhosOn:CloseLogonEventResponse */
class SOAP_CMAC _WhosOn__CloseLogonEventResponse
{
public:
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 13; } /* = unique id SOAP_TYPE__WhosOn__CloseLogonEventResponse */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         _WhosOn__CloseLogonEventResponse(): soap(NULL) { _WhosOn__CloseLogonEventResponse::soap_default(NULL); }
	virtual ~_WhosOn__CloseLogonEventResponse() { }
};
#endif

#ifndef SOAP_TYPE__WhosOn__DeleteLogonEvent
#define SOAP_TYPE__WhosOn__DeleteLogonEvent (14)
/* WhosOn:DeleteLogonEvent */
class SOAP_CMAC _WhosOn__DeleteLogonEvent
{
public:
	int eventID;	/* required element of type xsd:int */
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 14; } /* = unique id SOAP_TYPE__WhosOn__DeleteLogonEvent */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         _WhosOn__DeleteLogonEvent(): soap(NULL) { _WhosOn__DeleteLogonEvent::soap_default(NULL); }
	virtual ~_WhosOn__DeleteLogonEvent() { }
};
#endif

#ifndef SOAP_TYPE__WhosOn__DeleteLogonEventResponse
#define SOAP_TYPE__WhosOn__DeleteLogonEventResponse (15)
/* WhosOn:DeleteLogonEventResponse */
class SOAP_CMAC _WhosOn__DeleteLogonEventResponse
{
public:
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 15; } /* = unique id SOAP_TYPE__WhosOn__DeleteLogonEventResponse */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         _WhosOn__DeleteLogonEventResponse(): soap(NULL) { _WhosOn__DeleteLogonEventResponse::soap_default(NULL); }
	virtual ~_WhosOn__DeleteLogonEventResponse() { }
};
#endif

#ifndef SOAP_TYPE__WhosOn__FindLogonEvent
#define SOAP_TYPE__WhosOn__FindLogonEvent (16)
/* WhosOn:FindLogonEvent */
class SOAP_CMAC _WhosOn__FindLogonEvent
{
public:
	std::string *user;	/* optional element of type xsd:string */
	std::string *domain;	/* optional element of type xsd:string */
	std::string *computer;	/* optional element of type xsd:string */
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 16; } /* = unique id SOAP_TYPE__WhosOn__FindLogonEvent */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         _WhosOn__FindLogonEvent(): user(NULL), domain(NULL), computer(NULL), soap(NULL) { _WhosOn__FindLogonEvent::soap_default(NULL); }
	virtual ~_WhosOn__FindLogonEvent() { }
};
#endif

#ifndef SOAP_TYPE__WhosOn__FindLogonEventResponse
#define SOAP_TYPE__WhosOn__FindLogonEventResponse (17)
/* WhosOn:FindLogonEventResponse */
class SOAP_CMAC _WhosOn__FindLogonEventResponse
{
public:
	WhosOn__LogonEvent *FindLogonEventResult;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type WhosOn:LogonEvent */
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 17; } /* = unique id SOAP_TYPE__WhosOn__FindLogonEventResponse */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         _WhosOn__FindLogonEventResponse(): FindLogonEventResult(NULL), soap(NULL) { _WhosOn__FindLogonEventResponse::soap_default(NULL); }
	virtual ~_WhosOn__FindLogonEventResponse() { }
};
#endif

#ifndef SOAP_TYPE__WhosOn__FindLogonEvents
#define SOAP_TYPE__WhosOn__FindLogonEvents (18)
/* WhosOn:FindLogonEvents */
class SOAP_CMAC _WhosOn__FindLogonEvents
{
public:
	WhosOn__LogonEvent *filter;	/* required element of type WhosOn:LogonEvent */
	enum WhosOn__LogonEventMatch match;	/* required element of type WhosOn:LogonEventMatch */
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 18; } /* = unique id SOAP_TYPE__WhosOn__FindLogonEvents */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         _WhosOn__FindLogonEvents(): filter(NULL), soap(NULL) { _WhosOn__FindLogonEvents::soap_default(NULL); }
	virtual ~_WhosOn__FindLogonEvents() { }
};
#endif

#ifndef SOAP_TYPE__WhosOn__FindLogonEventsResponse
#define SOAP_TYPE__WhosOn__FindLogonEventsResponse (19)
/* WhosOn:FindLogonEventsResponse */
class SOAP_CMAC _WhosOn__FindLogonEventsResponse
{
public:
	WhosOn__ArrayOfLogonEvent *FindLogonEventsResult;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* optional element of type WhosOn:ArrayOfLogonEvent */
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 19; } /* = unique id SOAP_TYPE__WhosOn__FindLogonEventsResponse */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         _WhosOn__FindLogonEventsResponse(): FindLogonEventsResult(NULL), soap(NULL) { _WhosOn__FindLogonEventsResponse::soap_default(NULL); }
	virtual ~_WhosOn__FindLogonEventsResponse() { }
};
#endif

#ifndef SOAP_TYPE___ns1__CreateLogonEvent
#define SOAP_TYPE___ns1__CreateLogonEvent (31)
/* Operation wrapper: */
struct __ns1__CreateLogonEvent
{
public:
	_WhosOn__CreateLogonEvent *WhosOn__CreateLogonEvent;	/* optional element of type WhosOn:CreateLogonEvent */
};
#endif

#ifndef SOAP_TYPE___ns1__CloseLogonEvent
#define SOAP_TYPE___ns1__CloseLogonEvent (35)
/* Operation wrapper: */
struct __ns1__CloseLogonEvent
{
public:
	_WhosOn__CloseLogonEvent *WhosOn__CloseLogonEvent;	/* optional element of type WhosOn:CloseLogonEvent */
};
#endif

#ifndef SOAP_TYPE___ns1__DeleteLogonEvent
#define SOAP_TYPE___ns1__DeleteLogonEvent (39)
/* Operation wrapper: */
struct __ns1__DeleteLogonEvent
{
public:
	_WhosOn__DeleteLogonEvent *WhosOn__DeleteLogonEvent;	/* optional element of type WhosOn:DeleteLogonEvent */
};
#endif

#ifndef SOAP_TYPE___ns1__FindLogonEvent
#define SOAP_TYPE___ns1__FindLogonEvent (43)
/* Operation wrapper: */
struct __ns1__FindLogonEvent
{
public:
	_WhosOn__FindLogonEvent *WhosOn__FindLogonEvent;	/* optional element of type WhosOn:FindLogonEvent */
};
#endif

#ifndef SOAP_TYPE___ns1__FindLogonEvents
#define SOAP_TYPE___ns1__FindLogonEvents (47)
/* Operation wrapper: */
struct __ns1__FindLogonEvents
{
public:
	_WhosOn__FindLogonEvents *WhosOn__FindLogonEvents;	/* optional element of type WhosOn:FindLogonEvents */
};
#endif

#ifndef SOAP_TYPE___ns2__CreateLogonEvent
#define SOAP_TYPE___ns2__CreateLogonEvent (49)
/* Operation wrapper: */
struct __ns2__CreateLogonEvent
{
public:
	_WhosOn__CreateLogonEvent *WhosOn__CreateLogonEvent;	/* optional element of type WhosOn:CreateLogonEvent */
};
#endif

#ifndef SOAP_TYPE___ns2__CloseLogonEvent
#define SOAP_TYPE___ns2__CloseLogonEvent (51)
/* Operation wrapper: */
struct __ns2__CloseLogonEvent
{
public:
	_WhosOn__CloseLogonEvent *WhosOn__CloseLogonEvent;	/* optional element of type WhosOn:CloseLogonEvent */
};
#endif

#ifndef SOAP_TYPE___ns2__DeleteLogonEvent
#define SOAP_TYPE___ns2__DeleteLogonEvent (53)
/* Operation wrapper: */
struct __ns2__DeleteLogonEvent
{
public:
	_WhosOn__DeleteLogonEvent *WhosOn__DeleteLogonEvent;	/* optional element of type WhosOn:DeleteLogonEvent */
};
#endif

#ifndef SOAP_TYPE___ns2__FindLogonEvent
#define SOAP_TYPE___ns2__FindLogonEvent (55)
/* Operation wrapper: */
struct __ns2__FindLogonEvent
{
public:
	_WhosOn__FindLogonEvent *WhosOn__FindLogonEvent;	/* optional element of type WhosOn:FindLogonEvent */
};
#endif

#ifndef SOAP_TYPE___ns2__FindLogonEvents
#define SOAP_TYPE___ns2__FindLogonEvents (57)
/* Operation wrapper: */
struct __ns2__FindLogonEvents
{
public:
	_WhosOn__FindLogonEvents *WhosOn__FindLogonEvents;	/* optional element of type WhosOn:FindLogonEvents */
};
#endif

#ifndef SOAP_TYPE_SOAP_ENV__Header
#define SOAP_TYPE_SOAP_ENV__Header (58)
/* SOAP Header: */
struct SOAP_ENV__Header
{
#ifdef WITH_NOEMPTYSTRUCT
private:
	char dummy;	/* dummy member to enable compilation */
#endif
};
#endif

#ifndef SOAP_TYPE_SOAP_ENV__Code
#define SOAP_TYPE_SOAP_ENV__Code (59)
/* SOAP Fault Code: */
struct SOAP_ENV__Code
{
public:
	char *SOAP_ENV__Value;	/* optional element of type xsd:QName */
	struct SOAP_ENV__Code *SOAP_ENV__Subcode;	/* optional element of type SOAP-ENV:Code */
};
#endif

#ifndef SOAP_TYPE_SOAP_ENV__Detail
#define SOAP_TYPE_SOAP_ENV__Detail (61)
/* SOAP-ENV:Detail */
struct SOAP_ENV__Detail
{
public:
	int __type;	/* any type of element <fault> (defined below) */
	void *fault;	/* transient */
	char *__any;
};
#endif

#ifndef SOAP_TYPE_SOAP_ENV__Reason
#define SOAP_TYPE_SOAP_ENV__Reason (64)
/* SOAP-ENV:Reason */
struct SOAP_ENV__Reason
{
public:
	char *SOAP_ENV__Text;	/* optional element of type xsd:string */
};
#endif

#ifndef SOAP_TYPE_SOAP_ENV__Fault
#define SOAP_TYPE_SOAP_ENV__Fault (65)
/* SOAP Fault: */
struct SOAP_ENV__Fault
{
public:
	char *faultcode;	/* optional element of type xsd:QName */
	char *faultstring;	/* optional element of type xsd:string */
	char *faultactor;	/* optional element of type xsd:string */
	struct SOAP_ENV__Detail *detail;	/* optional element of type SOAP-ENV:Detail */
	struct SOAP_ENV__Code *SOAP_ENV__Code;	/* optional element of type SOAP-ENV:Code */
	struct SOAP_ENV__Reason *SOAP_ENV__Reason;	/* optional element of type SOAP-ENV:Reason */
	char *SOAP_ENV__Node;	/* optional element of type xsd:string */
	char *SOAP_ENV__Role;	/* optional element of type xsd:string */
	struct SOAP_ENV__Detail *SOAP_ENV__Detail;	/* optional element of type SOAP-ENV:Detail */
};
#endif

/******************************************************************************\
 *                                                                            *
 * Typedefs                                                                   *
 *                                                                            *
\******************************************************************************/

#ifndef SOAP_TYPE__QName
#define SOAP_TYPE__QName (5)
typedef char *_QName;
#endif

#ifndef SOAP_TYPE__XML
#define SOAP_TYPE__XML (6)
typedef char *_XML;
#endif


/******************************************************************************\
 *                                                                            *
 * Externals                                                                  *
 *                                                                            *
\******************************************************************************/


#endif

/* End of WhosOnStub.h */
