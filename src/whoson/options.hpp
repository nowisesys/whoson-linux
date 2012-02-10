#ifndef __OPTIONS_HPP__
#define __OPTIONS_HPP__

#include <string>

#include "whoson.hpp"

class Options
{
public:
	struct ArgumentException
	{
		std::string msg;
		ArgumentException(const std::string &msg) : msg(msg) {}
		ArgumentException(const char *opt);
	};
	
	enum Reason 
	{
		Logout, Login, List, Close, Session, Unknown
	};
	
	enum Format 
	{
		Compact, Human, Tabbed, XML
	};
	
	enum Option
	{
		OpLogon = 'i',   OpLogout = 'o',  OpList = 'l',     OpClose = 'F',  OpSession = 'S',
		OpHelp  = 'h',   OpVersion = 'V',
		
		OpId = 128,      OpStart = 129,   OpEnd = 130,      OpComp = 131,   OpHost = 132, 
		OpIp = 133,      OpHw = 134,      OpUser = 135,     OpDomain = 136,
		
		OpActive = 'a',  OpClosed = 'c',  OpBetween = 137,  OpBefore = 138, OpAfter = 139, OpExact = 'e',
		
	        OpHuman = 'H',   OpCompact = 'C', OpTabbed = 'T',   OpXml = 'X',
		OpVerbose = 'v', OpDebug = 'd',   OpEndpoint = 's'
	};
	
	Options();
	Options(SoapServiceProxy *proxy);
	void Parse(int argc, char **argv);     // throws ArgumentException
	
	SoapServiceProxy * GetServiceProxy() { return proxy; }
	void SetServiceProxy(SoapServiceProxy *proxy) { this->proxy = proxy; }
	
	Reason GetReason() const { return reason; }
	Format GetFormat() const { return format; }
	const WhosOn::LogonEvent * GetFilter() const { return &filter; }
	WhosOn::LogonEventMatch GetMatch() const { return match; }
	
	const char * GetEndpoint() const;
	
	int Verbose;
	bool Debug;
	
private:
	static void Usage();
	static void Version();
	
	void Show() const;
	
	Reason reason;
	Format format;
	WhosOn::LogonEvent filter;
	WhosOn::LogonEventMatch match;
	SoapServiceProxy *proxy;
};

#endif  // __OPTIONS_HPP__
