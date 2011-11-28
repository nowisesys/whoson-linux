#ifndef __LIBWHOSON_HPP__
#define __LIBWHOSON_HPP__

#include <vector>
#include <string>

class LogonEventServiceSoap12Proxy;      // SOAP 2.0 proxy
class LogonEventServiceSoapProxy;        // SOAP 1.1 proxy

#ifndef  WHOSON_SOAP_VERSION
# define WHOSON_SOAP_VERSION 12
#endif

#if WHOSON_SOAP_VERSION == 12
# define SoapServiceProxy LogonEventServiceSoap12Proxy
# include "soap/WhosOnLogonEventServiceSoap12Proxy.h"
#else
# define SoapServiceProxy LogonEventServiceSoapProxy
# include "soap/WhosOnLogonEventServiceSoapProxy.h"
#endif

namespace WhosOn {
	
	struct SoapServiceException 
	{
		SoapServiceProxy *proxy;
		SoapServiceException(SoapServiceProxy *proxy) : proxy(proxy) {}
		void Write(std::ostream &stream) const { proxy->soap_stream_fault(stream); }
	};

	struct LogonEvent
	{
		int eventID;
		std::string username;
		std::string domain;
		std::string hostname;
		std::string hwaddr;
		std::string ipaddr;
		time_t stime;
		time_t etime;
		std::string workstation;
		
		LogonEvent() : eventID(0), stime(0), etime(0) {}
		LogonEvent(int eventID) : eventID(eventID), stime(0), etime(0) {}
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
		
		int Add(const LogonEvent *event) const;
		int Add(const std::string &username, const std::string &domain) const;
		int Add(const std::string &username, const std::string &domain, const std::string &hwaddr, const std::string &workstation) const;
		
		void Close(int event) const;
		void Close(const LogonEvent *event) const;
		
		void Delete(int event) const;
		void Delete(const LogonEvent *event) const;
		
		std::vector<LogonEvent> Find(const LogonEvent *filter, LogonEventMatch match = MatchExact);
		LogonEvent Find(const std::string &username, const std::string &domain, const std::string &ipaddr);
		
		void SetProxy(SoapServiceProxy *proxy) { this->proxy = proxy; }
		SoapServiceProxy * GetProxy() const { return proxy; }
		
	private:
		SoapServiceProxy *proxy;
	};
	
	class LogonEventProxy : public LogonEvent
	{
	public:
		LogonEventProxy(int eventID);
		LogonEventProxy(const std::string &username, const std::string &domain);
		LogonEventProxy(const std::string &username, const std::string &domain, const std::string &hwaddr, const std::string &workstation);
		
		void Add(LogonEventAdapter *adapter);
		void Close(LogonEventAdapter *adapter);
		void Delete(LogonEventAdapter *adapter);
		
		std::vector<LogonEvent> Find(LogonEventAdapter *adapter, LogonEventMatch match = MatchExact);
	};
	
	inline void LogonEventAdapter::Close(const LogonEvent *event) const
	{
		Close(event->eventID);
	}
	
	inline void LogonEventAdapter::Delete(const LogonEvent *event) const
	{
		Delete(event->eventID);
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
	
	inline std::vector<LogonEvent> LogonEventProxy::Find(LogonEventAdapter *adapter, LogonEventMatch match)
	{
		return adapter->Find(this, match);
	}
	
}       // namespace WhosOn

#endif  // __LIBWHOSON_HPP__
