#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <iostream>
#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif
#include <getopt.h>

#include "options.hpp"

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
			break;
			
			// 
			// Reason:
			// 
		case OpLogon:
			break;
		case OpLogout:
			break;
		case OpList:
			break;
			
			// 
			// Filter:
			// 
		case OpId:
			break;
		case OpStart:
			break;
		case OpEnd:
			break;
		case OpComp:
			break;
		case OpHost:
			break;
		case OpIp:
			break;
		case OpHw:
			break;
		case OpUser:
			break;
		case OpDomain:
			break;
			
			// 
			// Match:
			// 
		case OpActive:
			break;
		case OpClosed:
			break;
		case OpBetween:
			break;
		case OpBefore:
			break;
		case OpAfter:
			break;
		case OpExact:
			break;
			
			// 
			// Format:
			// 
		case OpHuman:
			break;
		case OpCompact:
			break;
		case OpTabbed:
			break;
		case OpXml:
			break;
		}
	}
}
