// WhosOn Linux - Centralized Logon Accounting (WhosOn Program Suite).
// 
// Copyright (C) 2011-2018 Anders Lövgren, BMC-IT, Uppsala University.
// Copyright (C) 2018-2019 Anders Lövgren, Nowise Systems.
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
# include "config.h"
#endif

#include <iostream>
#if defined(HAVE_CSTDLIB)
# include <cstdlib>
#elif defined(HAVE_STDLIB_H)
# include <stdlib.h>
#endif

#include "whoson.hpp"     // library
#include "options.hpp"
#include "session.hpp"
#include "output.hpp"

class Application
{
public:
	Application(Options *options) : opts(options) 
	{
		opts->SetServiceProxy(&proxy);
		
		if(getenv("WHOSON_DEBUG")) {
			opts->Debug = atoi(getenv("WHOSON_DEBUG")) > 0;
		}
		if(getenv("WHOSON_VERBOSE")) {
			opts->Verbose = atoi(getenv("WHOSON_VERBOSE"));
		}
		if(getenv("WHOSON_SOAP_ENDPOINT")) {
			proxy.soap_endpoint = getenv("WHOSON_SOAP_ENDPOINT");
		}
		if(getenv("WHOSON_SOAP_USER")) {
			proxy.userid = getenv("WHOSON_SOAP_USER");
		}
		if(getenv("WHOSON_SOAP_PASS")) {
			proxy.passwd = getenv("WHOSON_SOAP_PASS");
		}
	}
	
	void Parse(int argc, char **argv)
	{
		try {
			opts->Parse("/etc/whoson.conf");
			opts->Parse("~/.whoson.conf");
			opts->Parse(argc, argv);
			if(opts->HasConfig()) {
				opts->Parse(opts->GetConfig());
			}
			if(opts->Debug) {
				opts->Write(std::cout);
			}
		} catch(Options::ArgumentException exception) {
			std::cerr << exception.msg << std::endl;
			exit(1);
		}
	}

	void Process() 
	{	
		WhosOn::LogonEventAdapter adapter(&proxy);
	
		try {
			switch(opts->GetReason()) {
			case Options::Login:
				Login(&adapter);
				break;
			case Options::Logout:
				Logout(&adapter);
				break;
			case Options::List:
				List(&adapter);
				break;
			case Options::Close:
				Close(&adapter);
				break;
			case Options::Session:
				WaitHandler(&adapter);
				break;
			case Options::Unknown:
				break;
			}
		} catch(WhosOn::SoapServiceException exception) {
			exception.Write(std::cerr);
			exit(1);
		}
	}
	
private:
	
	void Login(const WhosOn::LogonEventAdapter *adapter) const
	{
		adapter->Add();
	}

	void WaitHandler(const WhosOn::LogonEventAdapter *adapter) const
	{
		Session session(adapter, opts);
		try {
			session.Setup();
			session.Start();
		} catch(Session::Exception exception) {
			exception.Write();
			exit(1);
		}
	}
	
	void Logout(const WhosOn::LogonEventAdapter *adapter) const
	{
		WhosOn::LogonEvent event = adapter->Find();
		adapter->Close(&event);
	}
	
	void List(const WhosOn::LogonEventAdapter *adapter) const
	{
		std::vector<WhosOn::LogonEvent *> events;
		adapter->Find(events, opts->GetFilter(), opts->GetMatch());
		
		ProgramOutput output;
		switch(opts->GetFormat()) {
                case Options::Compact:
			output.SetFormat(new OutputFormatCompact());
			output.Write(&events);
			break;
		case Options::Human:
			output.SetFormat(new OutputFormatHuman());
			output.Write(&events);
			break;
		case Options::Tabbed:
			output.SetFormat(new OutputFormatTabbed());
			output.Write(&events);
			break;
		case Options::XML:
			output.SetFormat(new OutputFormatXML());
			output.Write(&events);
			break;
		}
	}
	
	void Close(const WhosOn::LogonEventAdapter *adapter) const 
	{
		std::vector<WhosOn::LogonEvent *> events;
		adapter->Find(events, opts->GetFilter(), opts->GetMatch());
		
		typedef std::vector<WhosOn::LogonEvent *>::const_iterator Iterator;
		for(Iterator it = events.begin(); it != events.end(); ++it) {
			adapter->Close(*it);
		}
	}
	
	SoapServiceProxy proxy;
	Options *opts;
};

int main(int argc, char **argv)
{
	Options options;
	Application app(&options);
	
	app.Parse(argc, argv);
	app.Process();
	
	return 0;
}
