#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "whoson.hpp"
#include "network.hpp"
#include "account.hpp"

#include "soap/LogonEventServiceSoap12.nsmap"
#include "soap/WhosOnLogonEventServiceSoap12Proxy.h"

namespace WhosOn {
	
	LogonEventProxy::LogonEventProxy(int eventID) : proxy(0) 
	{
		event.eventID = eventID;
	}
	
	LogonEventProxy::LogonEventProxy(const std::string &username, const std::string &domain) : proxy(0)
	{
		event.username = username;
		event.domain = domain;
	}
	
	LogonEventProxy::LogonEventProxy(const std::string &username, const std::string &domain, const std::string &hwaddr, const std::string &workstation) : proxy(0)
	{
		event.username = username;
		event.domain = domain;
		event.hwaddr = hwaddr;
		event.workstation = event.workstation;
	}

	LogonEventProxy::LogonEventProxy(const LogonEventProxy &proxy)
	{
		this->event = event;
		this->proxy = proxy.proxy;
	}
	
	LogonEventProxy::LogonEventProxy(const LogonEvent &event) : proxy(0)
	{
		this->event = event;
	}
	
	void LogonEventProxy::Add() const
	{
		// TODO: implement
	}
	
	void LogonEventProxy::Close() const
	{
		// TODO: implement
	}
	
	void LogonEventProxy::Delete() const
	{
		// TODO: implement
	}
	
	std::vector<LogonEvent> LogonEventProxy::Find() const
	{
		return Find(&event, MatchExact);    // Use Find(LogonEvent *, LogonEventMatch)
	}
	
	std::vector<LogonEvent> LogonEventProxy::Find(const LogonEvent *filter, LogonEventMatch match)
	{
		std::vector<LogonEvent> result;
		// TODO: implement
		return result;
	}
	
	LogonEvent LogonEventProxy::Find(const std::string &username, const std::string &domain, const std::string &ipaddr)
	{
		LogonEvent event;
		return event;
	}
		
	const LogonEvent * LogonEventProxy::GetLogonEvent() const
	{
		return &event;
	}
	
	void LogonEventProxy::SetEndpointAddress(const char *endpoint)
	{
		if(!proxy) {
			proxy = new LogonEventServiceSoap12Proxy();
		}
		proxy->soap_endpoint = endpoint;
	}

}       // namespace WhosOn
