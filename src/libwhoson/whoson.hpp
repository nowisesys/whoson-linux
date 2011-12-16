#ifndef __LIBWHOSON_HPP__
#define __LIBWHOSON_HPP__

#include <vector>
#include <string>

class LogonAccountingServiceSoap12Proxy;      // SOAP 2.0 proxy
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
	
	struct SoapServiceException 
	{
		SoapServiceProxy *proxy;
		SoapServiceException(SoapServiceProxy *proxy) : proxy(proxy) {}
		void Write(std::ostream &stream) const { proxy->soap_stream_fault(stream); }
	};

	struct LogonEvent : public WhosOn__LogonEvent
	{
		LogonEvent() {}
		LogonEvent(int EventID) { this->EventID = EventID; }
		virtual ~LogonEvent();
		
		operator int() { return EventID; }
		int GetEventID() const { return EventID; }
		
		void SetUsername(const std::string &user);
		void SetDomain(const std::string &domain);
		void SetHwAddress(const std::string &hwaddr);
		void SetIpAddress(const std::string &ipaddr);
		void SetHostname(const std::string &hostname);
		void SetWorkstation(const std::string &wksta);
		
		std::string GetUsername() const;
		std::string GetDomain() const;
		std::string GetHwAddress() const;
		std::string GetIpAddress() const;
		std::string GetHostname() const;
		std::string GetWorkstation() const;
		
		time_t GetStartTime() const { return StartTime; }
		time_t GetEndTime() const { return EndTime; }
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
		
		std::vector<LogonEvent *> Find(const LogonEvent *filter, LogonEventMatch match = MatchExact) const;
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
		
		std::vector<LogonEvent *> Find(LogonEventAdapter *adapter, LogonEventMatch match = MatchExact);
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
	
	inline std::vector<LogonEvent *> LogonEventProxy::Find(LogonEventAdapter *adapter, LogonEventMatch match)
	{
		return adapter->Find(this, match);
	}
	
}       // namespace WhosOn

#endif  // __LIBWHOSON_HPP__
