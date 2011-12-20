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
	}
	
	void Parse(int argc, char **argv)
	{
		try {
			opts->Parse(argc, argv);
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
