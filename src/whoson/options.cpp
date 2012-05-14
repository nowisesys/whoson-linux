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
#include "datetime.hpp"
#include "network.hpp"

Options::ArgumentException::ArgumentException(const char *opt)
{
	msg += "Unknown option '";
	msg += opt;
	msg += "'";
}

Options::Options() : proxy(0)
{
	reason = Unknown;
	format = Compact;
	match  = WhosOn::MatchExact;
}

Options::Options(SoapServiceProxy *proxy) : proxy(proxy)
{
	reason = Unknown;
	format = Compact;
	match  = WhosOn::MatchExact;
}

void Options::Usage()
{
	std::cout << PACKAGE_NAME << " - Client side application for the whoson logon accounting program suite.\n";
	std::cout 
		<< "\n"
		<< "Usage: " << PACKAGE_NAME << " [options...]\n"
		<< "Options:\n"
		<< "  -i,--logon:        Store logon event.\n"
		<< "  -o,--logout:       Store logoff event.\n"
		<< "  -l,--list:         List logon events (see filter and matching)\n"
		<< "  -F,--close:        Close matching sessions\n"
		<< "  -h,--help:         Show this help\n"
		<< "  -V,--version:      Get version info.\n"
		<< "  -v,--verbose:      Be more verbose.\n"
		<< "  -d,--debug:        Enable debug mode.\n"
		<< "  -S,--session:      Use session mode (login on start/logout on exit).\n"
		<< "Filters:\n"
		<< "     --id=num:       Filter on event ID.\n"
		<< "     --start=date:   Filter on start date.\n"
		<< "     --end=date:     Filter on end date.\n"
		<< "     --comp=name:    Filter on computer name (NetBIOS).\n"
		<< "     --host=name:    Filter on computer name (FQHN).\n"
		<< "     --ip=addr:      Filter on IP address.\n"
		<< "     --hw=addr:      Filter on MAC address.\n"
		<< "     --user=name:    Filter on username.\n"
		<< "     --domain=name:  Filter on domain name.\n"
		<< "     --first=num:    Filter on event ID.\n"
		<< "     --last=num:     Filter on event ID.\n"
		<< "  -L,--limit=num:    Limit number of rows returned.\n"
		<< "Matching:\n"
		<< "  -a,--active:       Match active logons.\n"
		<< "  -c,--closed:       Match closed logons.\n"
		<< "     --between:      Match logons between.\n"
		<< "     --before:       Match logons before.\n"
		<< "     --after:        Match logons after.\n"
		<< "  -e,--exact:        Match filter exact.\n"
		<< "  -t,--this:         This host is implied.\n"
		<< "Format:\n"
		<< "  -H,--human:        Output formatted for human reading.\n"
		<< "  -C,--compact:      Output formatted in compact style.\n"
		<< "  -T,--tabbed:       Output in tab separated format.\n"
		<< "  -X,--XML:          Output formatted as XML.\n"
		<< "SOAP:\n"
		<< "  -s,--endpoint=url: The SOAP service endpoint.\n"
		<< "\n"
		<< "Notes:\n"
		<< "1. The --between, --before and --after is limited to datetime (--start/--end) and ID (--first/--last) filtering.\n"
		<< "2. The --active and --closed option can only be used with exact matching filter options, like --host=xxx.\n"
		<< "\n"
		<< "Copyright (C) 2011-2012 Anders Lövgren (QNET/Compdept BMC)\n";
}

void Options::Version()
{
	std::cout << PACKAGE_STRING << std::endl;
}

void Options::Show() const
{
	const char *mReason[] = { "Logout", "Login", "List", "Close", "Session", "Unknown" };
	const char *mFormat[] = { "Compact", "Human", "Tabbed", "XML" };
	const char *mMatch[]  = { "Before", "Between", "After", "Exact", "Active", "Closed" };
	
	std::cout 
		<< "Options: " << "\n"
		<< "  Reason: " << mReason[reason] << "\n"
		<< "  Format: " << mFormat[format] << "\n"
		<< "  Match:  " << mMatch[match] << "\n"
		<< "  Filter: \n"
		<< "  --------------------------------------\n"
		<< "       Event ID: " << filter.EventID << "\n"
		<< "     Start Time: " << filter.StartTime << "\n"
		<< "       End Time: " << filter.EndTime << "\n"
		<< "       Computer: " << filter.Workstation << "\n"
		<< "       Hostname: " << filter.Hostname << "\n"
		<< "     IP-address: " << filter.IpAddress << "\n"
		<< "    MAC-address: " << filter.HwAddress << "\n"
		<< "       Username: " << filter.Username << "\n"
		<< "         Domain: " << filter.Domain << "\n"
		<< "          First: " << filter.FirstID << "\n"
		<< "           Last: " << filter.LastID << "\n"
		<< "          Limit: " << filter.Limit << "\n"
		<< "  SOAP:\n"
		<< "  --------------------------------------\n"
		<< "       Endpoint: " << GetEndpoint() << "\n"
		<< std::endl;
}

const char * Options::GetEndpoint() const
{
	return (proxy && proxy->soap_endpoint) ? proxy->soap_endpoint : "";
}

void Options::Parse(int argc, char **argv)
{
	int c, index;
	const option longopts[] = {
		// Generic:
		{ "help",     0, 0, OpHelp },
		{ "version",  0, 0, OpVersion },
		{ "verbose",  0, 0, OpVerbose },
		{ "debug",    0, 0, OpDebug },
		// Reason:
		{ "logon",    0, 0, OpLogon },
		{ "logout",   0, 0, OpLogout },
		{ "list",     0, 0, OpList },
		{ "close",    0, 0, OpClose },
		{ "session",  0, 0, OpSession },
		{ "wait",     0, 0, OpSession }, // alias
		// Filter:
		{ "id",       1, 0, OpId },
		{ "start",    1, 0, OpStart },
		{ "end",      1, 0, OpEnd },
		{ "comp",     1, 0, OpComp },
		{ "host",     1, 0, OpHost },
		{ "ip",       1, 0, OpIp },
		{ "ipaddr",   1, 0, OpIp },      // alias
		{ "hw",       1, 0, OpHw },
		{ "hwaddr",   1, 0, OpHw },      // alias
		{ "mac",      1, 0, OpHw },      // alias
		{ "user",     1, 0, OpUser },
		{ "username", 1, 0, OpUser },    // alias
		{ "domain",   1, 0, OpDomain },
		{ "first",    1, 0, OpFirst },
		{ "last",     1, 0, OpLast },
		{ "limit",    1, 0, OpLimit },
		// Match:
		{ "active",   0, 0, OpActive },
		{ "closed",   0, 0, OpClosed },
		{ "between",  0, 0, OpBetween },
		{ "before",   0, 0, OpBefore },
		{ "after",    0, 0, OpAfter },
		{ "exact",    0, 0, OpExact },
		{ "this",     0, 0, OpThis },
		// Format:
		{ "human",    0, 0, OpHuman },
		{ "compact",  0, 0, OpCompact },
		{ "tabbed",   0, 0, OpTabbed },
		{ "XML",      0, 0, OpXml },
		{ "xml",      0, 0, OpXml },     // alias
		// SOAP:
		{ "endpoint", 1, 0, OpEndpoint },
		{ 0, 0, 0, 0 }
	};
	
	opterr = 0;
	
	while((c = getopt_long(argc, argv, "acCdeFhHilL:os:StTvVX", longopts, &index)) != -1) {
		switch(c) {
		case OpHelp:
			Usage();
			exit(0);
			break;
		case OpVersion:
			Version();
			exit(0);
			break;
		case OpVerbose:
			Verbose++;
			break;
		case OpDebug:
			Debug = true;
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
		case OpClose:
			reason = Close;
			break;
		case OpSession:
			reason = Session;
			break;
			
			// 
			// Filter:
			// 
		case OpId:
			filter.EventID = atoi(optarg);
			break;
		case OpStart:
			filter.StartTime = DateTime(optarg);
			break;
		case OpEnd:
			filter.EndTime = DateTime(optarg);
			break;
		case OpComp:
			filter.Workstation = optarg;
			break;
		case OpHost:
			filter.Hostname = optarg;
			break;
		case OpIp:
			filter.IpAddress = optarg;
			break;
		case OpHw:
			filter.HwAddress = optarg;
			break;
		case OpUser:
			filter.Username = optarg;
			break;
		case OpDomain:
			filter.Domain = optarg;
			break;
		case OpFirst:
			filter.FirstID = atoi(optarg);
			break;
		case OpLast:
			filter.LastID = atoi(optarg);
			break;
		case OpLimit:
			filter.Limit = atoi(optarg);
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
		case OpThis:
			{
				const WhosOn::Network *network = WhosOn::Network::GetInstance();
				filter.Workstation = network->GetComputer();
				filter.HwAddress = network->GetMacAddress();
			}
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

			//
			// SOAP:
			// 
		case OpEndpoint:
			if(proxy) {
				proxy->soap_endpoint = optarg;
			}
			break;

		default:
			throw ArgumentException(argv[--optind]);
		}
	}
	
	if(Debug) {
		Show();
	}
	
	if(reason == Unknown) {
		std::string msg = "Missing -o or -i option, see --help";
		throw ArgumentException(msg);
	}
}
