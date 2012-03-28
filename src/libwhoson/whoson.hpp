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

#ifndef __LIBWHOSON_HPP__
#define __LIBWHOSON_HPP__

#include <vector>
#include <string>

class LogonAccountingServiceSoap12Proxy;      // SOAP 1.2 proxy
class LogonAccountingServiceSoapProxy;        // SOAP 1.1 proxy

#ifndef  WHOSON_SOAP_VERSION
# define WHOSON_SOAP_VERSION 12
#endif

#if WHOSON_SOAP_VERSION == 12
# define SoapServiceProxy LogonAccountingServiceSoap12Proxy
# include "soap/WhosOnLogonAccountingServiceSoap12Proxy.h"
#else
# define SoapServiceProxy LogonAccountingServiceSoapProxy
# include "soap/WhosOnLogonAccountingServiceSoapProxy.h"
#endif

namespace WhosOn {

	typedef WhosOn__LogonEvent LogonEvent;
	
	struct SoapServiceException 
	{
		SoapServiceProxy *proxy;
		SoapServiceException(SoapServiceProxy *proxy) : proxy(proxy) {}
		void Write(std::ostream &stream) const { proxy->soap_stream_fault(stream); }
	};
	
	enum LogonEventMatch
	{
		MatchBefore = 0, MatchBetween = 1, MatchAfter = 2, MatchExact = 3, 
		MatchActive = 4, MatchClosed = 5
	};
	
	class LogonEventAdapter
	{
	public:
		LogonEventAdapter(SoapServiceProxy *proxy);

		int Add() const;
		int Add(const LogonEvent *event) const;
		int Add(const std::string &username, const std::string &domain) const;
		int Add(const std::string &username, const std::string &domain, const std::string &hwaddr, const std::string &workstation) const;
		
		void Close(int event) const;
		void Close(const LogonEvent *event) const;
		
		void Delete(int event) const;
		void Delete(const LogonEvent *event) const;
		
		void Find(std::vector<LogonEvent *> &result, const LogonEvent *filter, LogonEventMatch match = MatchExact) const;
		LogonEvent Find(const std::string &username, const std::string &domain, const std::string &workstation) const;
		LogonEvent Find() const;    // Detect user and computer.
		
		void SetProxy(SoapServiceProxy *proxy) { this->proxy = proxy; }
		SoapServiceProxy * GetProxy() const { return proxy; }
		
	private:
		SoapServiceProxy *proxy;
	};
	
	class LogonEventProxy : private LogonEvent
	{
	public:
		LogonEventProxy(int eventID);
		LogonEventProxy(const std::string &username, const std::string &domain);
		LogonEventProxy(const std::string &username, const std::string &domain, const std::string &hwaddr, const std::string &workstation);
		
		void Add(LogonEventAdapter *adapter);
		void Close(LogonEventAdapter *adapter);
		void Delete(LogonEventAdapter *adapter);
		
		void Find(std::vector<LogonEvent *> &result, LogonEventAdapter *adapter, LogonEventMatch match = MatchExact);
	};
	
	inline void LogonEventAdapter::Close(const LogonEvent *event) const
	{
		Close(event->EventID);
	}
	
	inline void LogonEventAdapter::Delete(const LogonEvent *event) const
	{
		Delete(event->EventID);
	}
	
	inline void LogonEventProxy::Add(LogonEventAdapter *adapter) 
	{
		adapter->Add(this);
	}
	
	inline void LogonEventProxy::Close(LogonEventAdapter *adapter)
	{
		adapter->Close(this);
	}
	
	inline void LogonEventProxy::Delete(LogonEventAdapter *adapter)
	{
		adapter->Delete(this);
	}
	
	inline void LogonEventProxy::Find(std::vector<LogonEvent *> &result, LogonEventAdapter *adapter, LogonEventMatch match)
	{
		return adapter->Find(result, this, match);
	}
	
}       // namespace WhosOn

#endif  // __LIBWHOSON_HPP__
