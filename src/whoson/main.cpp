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

class Application
{
public:
	Application(Options *options) : opts(options) 
	{
		if(getenv("WHOSON_DEBUG")) {
			opts->Debug = atoi("WHOSON_DEBUG") > 0;
		}
		if(getenv("WHOSON_VERBOSE")) {
			opts->Verbose = atoi("WHOSON_VERBOSE");
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
				adapter.Add(opts->GetFilter());
				break;
			case Options::Logout:
				adapter.Close(opts->GetFilter());
				break;
			case Options::List:
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
