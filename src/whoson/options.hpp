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
		OpLogon = 'i',    OpLogout = 'o',   OpList = 'l',     OpClose = 'F',  OpSession = 'S',
		OpHelp  = 'h',    OpVersion = 'V',  OpConfig = 'f',
		
		OpId = 128,       OpStart = 129,    OpEnd = 130,      OpComp = 131,   OpHost = 132, 
		OpIp = 133,       OpHw = 134,       OpUser = 135,     OpDomain = 136,
		OpFirst = 140,    OpLast = 141,     OpLimit = 'L',
		
		OpActive = 'a',   OpClosed = 'c',   OpBetween = 137,  OpBefore = 138, OpAfter = 139, OpExact = 'e',
	        OpThis = 't',
		
	        OpHuman = 'H',    OpCompact = 'C',  OpTabbed = 'T',   OpXml = 'X',
		OpVerbose = 'v',  OpDebug = 'd',   
                
                OpEndpoint = 's', OpSoapUser = 'U', OpSoapPass = 'P'
	};
	
	Options();
	Options(SoapServiceProxy *proxy);
	
	void Parse(int argc, char **argv);     // throws ArgumentException
	void Parse(const char *file);          // throws ArgumentException
	void Parse(std::string file);          // throws ArgumentException
	
	SoapServiceProxy * GetServiceProxy() { return proxy; }
	void SetServiceProxy(SoapServiceProxy *proxy) { this->proxy = proxy; }
		
	Reason GetReason() const { return reason; }
	Format GetFormat() const { return format; }
	const WhosOn::LogonEvent * GetFilter() const { return &filter; }
	WhosOn::LogonEventMatch GetMatch() const { return match; }
	
        const char * GetSoapUser() const;
        const char * GetSoapPass() const;
	const char * GetEndpoint() const;
        
	const char * GetConfig() const { return config; }
	bool HasConfig() const { return config != 0; }
	
	void Write(std::ostream &) const;
	void Show() const;
	
	int Verbose;
	bool Debug;
	
private:
	static void Usage();
	static void Version();	
	
	Reason reason;
	Format format;
	WhosOn::LogonEvent filter;
	WhosOn::LogonEventMatch match;
	SoapServiceProxy *proxy;
	
	const char *config;
};

#endif  // __OPTIONS_HPP__
