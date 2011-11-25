#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <iostream>
#if defined(HAVE_CTIME)
# include <ctime>
#else
# include <time.h>
#endif
#if defined(HAVE_CSTDLIB)
# include <cstdlib>
#elif defined(HAVE_STDLIB_H)
# include <stdlib.h>
#endif
#include <getopt.h>

#include "options.hpp"

Options::ArgumentException::ArgumentException(const char *opt)
{
	msg += "Unknown option '";
	msg += opt;
	msg += "'";
}

void Options::Usage()
{
	std::cout << PACKAGE_NAME << " - Client side application for the whoson logon accounting program suite.\n";
	std::cout 
		<< "\n"
		<< "Usage: whoson.exe [options...]\n"
		<< "Options:\n"
		<< "  -i,--logon:       Store logon event.\n"
		<< "  -o,--logout:      Store logoff event.\n"
		<< "  -l,--list:        List logon events (see filter and matching)\n"
		<< "  -h,--help:        Show this help\n"
		<< "  -V,--version:     Get version info.\n"
		<< "Filters:\n"
		<< "     --id=num:      Filter on event ID.\n"
		<< "     --start=date:  Filter on start date.\n"
		<< "     --end=date:    Filter on end date.\n"
		<< "     --comp=name:   Filter on computer name (NetBIOS).\n"
		<< "     --host=name:   Filter on computer name (FQHN).\n"
		<< "     --ip=addr:     Filter on IP address.\n"
		<< "     --hw=addr:     Filter on MAC address.\n"
		<< "     --user=name:   Filter on username.\n"
		<< "     --domain=name: Filter on domain name.\n"
		<< "Matching:\n"
		<< "  -a,--active:      Match active logons.\n"
		<< "  -c,--closed:      Match closed logons.\n"
		<< "     --between:     Match logons between.\n"
		<< "     --before:      Match logons before.\n"
		<< "     --after:       Match logons after.\n"
		<< "  -e,--exact:       Match filter exact.\n"
		<< "Format:\n"
		<< "  -H,--human:       Output formatted for human reading.\n"
		<< "  -C,--compact:     Output formatted in compact style.\n"
		<< "  -T,--tabbed:      Output in tab separated format.\n"
		<< "  -X,--XML:         Output formatted as XML.\n"
		<< "\n"
		<< "The --between, --before and --after can only be used with the --start, --end (and --id) filter.\n"
		<< "\n"
		<< "Copyright (C) 2011 Anders Lövgren (QNET/Compdept BMC)\n";
}

void Options::Version()
{
	std::cout << PACKAGE_STRING << std::endl;
}

void Options::Parse(int argc, char **argv)
{
	int c, index;
	const option longopts[] = {
		{ "logon", 0, 0, OpLogon },
		{ "logout", 0, 0, OpLogout },
		{ "list", 0, 0, OpList },
		{ "help", 0, 0, OpHelp },
		{ "version", 0, 0, OpVersion },
		{ "id", 1, 0, OpId },
		{ "start", 1, 0, OpStart },
		{ 0, 0, 0, 0 }
	};
	
	while((c = getopt_long(argc, argv, "iolhVaceHCTX", longopts, &index)) != -1) {
		std::cout << "Option: " << c << std::endl;
		
		switch(c) {
		case OpHelp:
			Usage();
			exit(0);
			break;
		case OpVersion:
			Version();
			exit(0);
			break;
			
			// 
			// Reason:
			// 
		case OpLogon:
			reason = Login;
			break;
		case OpLogout:
			reason = Logout;
			break;
		case OpList:
			reason = List;
			break;
			
			// 
			// Filter:
			// 
		case OpId:
			filter.eventID = atoi(optarg);
			break;
		case OpStart:
			filter.stime = mktime(getdate(optarg));
			break;
		case OpEnd:
			filter.etime = mktime(getdate(optarg));
			break;
		case OpComp:
			filter.workstation = optarg;
			break;
		case OpHost:
			filter.hostname = optarg;
			break;
		case OpIp:
			filter.ipaddr = optarg;
			break;
		case OpHw:
			filter.hwaddr = optarg;
			break;
		case OpUser:
			filter.username = optarg;
			break;
		case OpDomain:
			filter.domain = optarg;
			break;
			
			// 
			// Match:
			// 
		case OpActive:
			match = WhosOn::MatchActive;
			break;
		case OpClosed:
			match = WhosOn::MatchClosed;			
			break;
		case OpBetween:
			match = WhosOn::MatchBetween;
			break;
		case OpBefore:
			match = WhosOn::MatchBefore;
			break;
		case OpAfter:
			match = WhosOn::MatchAfter;
			break;
		case OpExact:
			match = WhosOn::MatchExact;
			break;
			
			// 
			// Format:
			// 
		case OpHuman:
			format = Human;
			break;
		case OpCompact:
			format = Compact;
			break;
		case OpTabbed:
			format = Tabbed;
			break;
		case OpXml:
			format = XML;
			break;
			
		default:
			throw ArgumentException(optarg);
		}
	}
	
	if(reason == Unknown) {
		std::string msg = "Missing -o or -i option, see --help";
		throw ArgumentException(msg);
	}
}
