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
#else
# define SoapServiceProxy LogonEventServiceSoapProxy
#endif

namespace WhosOn {

	struct ArgumentException
	{
		std::string msg;
		ArgumentException(const std::string &msg) { this->msg = msg; }
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
	};
	
	enum LogonEventMatch
	{
		MatchBefore = 0, MatchBetween = 1, MatchAfter = 2, MatchExact = 3, 
		MatchActive = 4, MatchClosed = 5
	};
	
	class LogonEventProxy 
	{
	public:
		LogonEventProxy(int eventID);
		LogonEventProxy(const std::string &username, const std::string &domain);
		LogonEventProxy(const std::string &username, const std::string &domain, const std::string &hwaddr, const std::string &workstation);
		LogonEventProxy(const LogonEventProxy &);
		LogonEventProxy(const LogonEvent &);
		~LogonEventProxy();
		
		void Add() const;
		void Close() const;
		void Delete() const;
		
		std::vector<LogonEvent> Find() const;
		static std::vector<LogonEvent> Find(const LogonEvent *filter, LogonEventMatch match = MatchExact);
		static LogonEvent Find(const std::string &username, const std::string &domain, const std::string &ipaddr);
		
		const LogonEvent * GetLogonEvent() const;
		void SetEndpointAddress(const char *endpoint);
		
		SoapServiceProxy * GetProxy() const { return proxy; }
		void SetProxy(SoapServiceProxy *proxy) { this->proxy = proxy; }
		
	private:
		LogonEvent event;
		SoapServiceProxy *proxy;
	};
}

#endif  // __LIBWHOSON_HPP__
