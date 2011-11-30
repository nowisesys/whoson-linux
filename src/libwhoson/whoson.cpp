#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "whoson.hpp"
#include "network.hpp"
#include "account.hpp"

#include "soap/LogonEventServiceSoap12.nsmap"
#include "soap/WhosOnLogonEventServiceSoap12Proxy.h"

namespace WhosOn {

	LogonEventAdapter::LogonEventAdapter(SoapServiceProxy *proxy)
		: proxy(proxy)
	{
	}
		
	int LogonEventAdapter::Add(const LogonEvent *event) const
	{
		return Add(event->username, event->domain, event->hwaddr, event->workstation);
	}

	int LogonEventAdapter::Add() const
	{
		const Network *net = Network::GetInstance();
		const Account *acc = Account::GetInstance();
		return Add(acc->GetUsername(), acc->GetDomain(), net->GetMacAddress(), net->GetComputer());
	}
	
	int LogonEventAdapter::Add(const std::string &username, const std::string &domain) const
	{
		const Network *net = Network::GetInstance();
		return Add(username, domain, net->GetMacAddress(), net->GetComputer());
	}
	
	int LogonEventAdapter::Add(const std::string &username, const std::string &domain, const std::string &hwaddr, const std::string &workstation) const
	{
		_WhosOn__CreateLogonEvent args;
		_WhosOn__CreateLogonEventResponse resp;
		
		args.user = (std::string *)&username;
		args.domain = (std::string *)&domain;
		args.hwaddr = (std::string *)&hwaddr;
		args.computer = (std::string *)&workstation;
		
		if(proxy->CreateLogonEvent(&args, &resp) != SOAP_OK) {
			throw SoapServiceException(proxy);
		} else {
			return resp.CreateLogonEventResult;
		}
	}
		
	void LogonEventAdapter::Close(int event) const
	{
		_WhosOn__CloseLogonEvent args;
		_WhosOn__CloseLogonEventResponse resp;
		
		args.eventID = event;
		if(proxy->CloseLogonEvent(&args, &resp) != SOAP_OK) {
			throw SoapServiceException(proxy);
		}
	}
		
	void LogonEventAdapter::Delete(int event) const
	{
		_WhosOn__DeleteLogonEvent args;
		_WhosOn__DeleteLogonEventResponse resp;
		
		args.eventID = event;
		if(proxy->DeleteLogonEvent(&args, &resp) != SOAP_OK) {
			throw SoapServiceException(proxy);
		}
	}
  
	std::vector<LogonEvent> LogonEventAdapter::Find(const LogonEvent *filter, LogonEventMatch match)
	{
		// TODO: implement
	}
	
	LogonEvent LogonEventAdapter::Find(const std::string &username, const std::string &domain, const std::string &ipaddr)
	{
		// TODO: implement
	}
		
	LogonEventProxy::LogonEventProxy(int eventID) 
		: LogonEvent(eventID)
	{
	}
	
	LogonEventProxy::LogonEventProxy(const std::string &username, const std::string &domain) 
		: LogonEvent(0)
	{
		this->username = username;
		this->domain = domain;
	}
	
	LogonEventProxy::LogonEventProxy(const std::string &username, const std::string &domain, const std::string &hwaddr, const std::string &workstation)
		: LogonEvent(0)
	{
		this->username = username;
		this->domain = domain;
		this->hwaddr = hwaddr;
		this->workstation = workstation;
	}

}       // namespace WhosOn
