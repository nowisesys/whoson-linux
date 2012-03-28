// WhosOn Linux - Centralized Logon Accounting (WhosOn Program Suite).
// 
// Copyright (C) 2011-2012 Anders Lövgren, Computing Department at BMC,
// Uppsala Biomedical Centre, Uppsala University.
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
// 

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "whoson.hpp"
#include "network.hpp"
#include "account.hpp"

#include "soap/LogonAccountingServiceSoap12.nsmap"
#include "soap/WhosOnLogonAccountingServiceSoap12Proxy.h"

namespace WhosOn {

	LogonEventAdapter::LogonEventAdapter(SoapServiceProxy *proxy)
		: proxy(proxy)
	{
	}
		
	int LogonEventAdapter::Add(const LogonEvent *event) const
	{
		return Add(event->Username, event->Domain, event->HwAddress, event->Workstation);
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
		
		args.user = username;
		args.domain = domain;
		args.hwaddr = hwaddr;
		args.computer = workstation;
		
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
  
	void LogonEventAdapter::Find(std::vector<LogonEvent *> &result, const LogonEvent *filter, LogonEventMatch match) const
	{
		_WhosOn__FindLogonEvents args;
		_WhosOn__FindLogonEventsResponse resp;
		
		args.filter = (WhosOn__LogonEvent *)filter;
		args.match  = (WhosOn__LogonEventMatch)match;
		
		if(proxy->FindLogonEvents(&args, &resp) != SOAP_OK) {
			throw SoapServiceException(proxy);
		}
		
		result = resp.FindLogonEventsResult->LogonEvent;
	}
	
	LogonEvent LogonEventAdapter::Find(const std::string &username, const std::string &domain, const std::string &workstation) const
	{
		_WhosOn__FindLogonEvent args;
		_WhosOn__FindLogonEventResponse resp;
		
		args.user = username;
		args.domain = domain;
		args.computer = workstation;

		if(proxy->FindLogonEvent(&args, &resp) != SOAP_OK) {
			throw SoapServiceException(proxy);
		}
		
		return *resp.FindLogonEventResult;
	}
	
	LogonEvent LogonEventAdapter::Find() const
	{
		const Network *net = Network::GetInstance();
		const Account *acc = Account::GetInstance();
		
		return Find(acc->GetUsername(), acc->GetDomain(), net->GetComputer());
	}
	
	LogonEventProxy::LogonEventProxy(int eventID) 
	{
		this->EventID = eventID;
	}
	
	LogonEventProxy::LogonEventProxy(const std::string &username, const std::string &domain) 
	{
		this->Username = username;
		this->Domain = domain;
	}
	
	LogonEventProxy::LogonEventProxy(const std::string &username, const std::string &domain, const std::string &hwaddr, const std::string &workstation)
	{
		this->Username = username;
		this->Domain = domain;
		this->HwAddress = hwaddr;
		this->Workstation = workstation;
	}

}       // namespace WhosOn
