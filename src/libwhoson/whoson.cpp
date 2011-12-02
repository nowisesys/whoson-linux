#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "whoson.hpp"
#include "network.hpp"
#include "account.hpp"

#include "soap/LogonEventServiceSoap12.nsmap"
#include "soap/WhosOnLogonEventServiceSoap12Proxy.h"

namespace WhosOn {
	
	LogonEvent::~LogonEvent()
	{
	}
	
#define SetMember(m, v) { if(m) delete m; m = new std::string(v); }
#define GetMember(m)    m ? *m : ""
	
	void LogonEvent::SetUsername(const std::string &user)     { SetMember(this->Username, user); }
	void LogonEvent::SetDomain(const std::string &domain)     { SetMember(this->Domain, domain); }
	void LogonEvent::SetHwAddress(const std::string &hwaddr)  { SetMember(this->HwAddress, hwaddr); }
	void LogonEvent::SetIpAddress(const std::string &ipaddr)  { SetMember(this->IpAddress, ipaddr); }
	void LogonEvent::SetHostname(const std::string &hostname) { SetMember(this->Hostname, hostname); }
	void LogonEvent::SetWorkstation(const std::string &wksta) { SetMember(this->Workstation, wksta); }

	std::string LogonEvent::GetUsername() const    { return GetMember(Username); }
	std::string LogonEvent::GetDomain() const      { return GetMember(Domain); }
	std::string LogonEvent::GetHwAddress() const   { return GetMember(HwAddress); }
	std::string LogonEvent::GetIpAddress() const   { return GetMember(IpAddress); }
	std::string LogonEvent::GetHostname() const    { return GetMember(Hostname); }
	std::string LogonEvent::GetWorkstation() const { return GetMember(Workstation); }
	
	LogonEventAdapter::LogonEventAdapter(SoapServiceProxy *proxy)
		: proxy(proxy)
	{
	}
		
	int LogonEventAdapter::Add(const LogonEvent *event) const
	{
		return Add(*event->Username, *event->Domain, *event->HwAddress, *event->Workstation);
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
  
	std::vector<LogonEvent *> LogonEventAdapter::Find(const LogonEvent *filter, LogonEventMatch match) const
	{
		// TODO: implement
	}
	
	LogonEvent LogonEventAdapter::Find(const std::string &username, const std::string &domain, const std::string &workstation) const
	{
		_WhosOn__FindLogonEvent args;
		_WhosOn__FindLogonEventResponse resp;
		
		args.user = (std::string *)&username;
		args.domain = (std::string *)&domain;
		args.computer = (std::string *)&workstation;

		if(proxy->FindLogonEvent(&args, &resp) != SOAP_OK) {
			throw SoapServiceException(proxy);
		}
	}
	
	LogonEvent LogonEventAdapter::Find() const
	{
		const Network *net = Network::GetInstance();
		const Account *acc = Account::GetInstance();
		
		return Find(acc->GetUsername(), acc->GetDomain(), net->GetComputer());
	}
	
	LogonEventProxy::LogonEventProxy(int eventID) 
		: LogonEvent(eventID)
	{
	}
	
	LogonEventProxy::LogonEventProxy(const std::string &username, const std::string &domain) 
		: LogonEvent(0)
	{
		this->Username = (std::string *)&username;
		this->Domain = (std::string *)&domain;
	}
	
	LogonEventProxy::LogonEventProxy(const std::string &username, const std::string &domain, const std::string &hwaddr, const std::string &workstation)
		: LogonEvent(0)
	{
		this->Username = (std::string *)&username;
		this->Domain = (std::string *)&domain;
		this->HwAddress = (std::string *)&hwaddr;
		this->Workstation = (std::string *)&workstation;
	}

}       // namespace WhosOn
