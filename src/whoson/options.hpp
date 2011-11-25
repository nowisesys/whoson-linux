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
		Logout, Login, List, Unknown
	};
	
	enum Format 
	{
		Compact, Human, Tabbed, XML
	};
	
	enum Option
	{
		OpLogon = 'i',  OpLogout = 'o',  OpList = 'l',    OpHelp = 'h',   OpVersion = 'V',
		OpId = 128,     OpStart = 129,   OpEnd = 130,     OpComp = 131,   OpHost = 132, 
		OpIp = 133,     OpHw = 134,      OpUser = 135,    OpDomain = 136,
		OpActive = 'a', OpClosed = 'c',  OpBetween = 137, OpBefore = 138, OpAfter = 139, OpExact = 'e',
		OpHuman = 'H',  OpCompact = 'C', OpTabbed = 'T',  OpXml = 'X'
	};
	
	void Parse(int argc, char **argv);     // throws ArgumentException
	Reason GetReason() const { return reason; }
	Format GetFormat() const { return format; }
	const WhosOn::LogonEvent * GetFilter() const { return &filter; }
	WhosOn::LogonEventMatch GetMatch() const { return match; }
	
private:
	static void Usage();
	static void Version();
	
	Reason reason;
	Format format;
	WhosOn::LogonEvent filter;
	WhosOn::LogonEventMatch match;
};

#endif  // __OPTIONS_HPP__
