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

#ifdef HAVE_ARPA_INET_H
# include <arpa/inet.h>
#endif
#include <net/if.h>
#ifdef HAVE_STDINT_H
# include <stdint.h>
#endif
#include <stdio.h>
#include <netdb.h>

#ifdef HAVE_LIBWBCLIENT
extern "C" {
#include <wbclient.h>
}
#endif

#include "network.hpp"

extern "C" {
	extern int get_default_route_iface(struct ifreq *req, const char **call, int *code);
	extern const char * get_iface_name(const struct ifreq *req);
	extern const struct sockaddr * get_mac_addr(const struct ifreq *req);
}

namespace WhosOn {
	
#ifdef HAVE_LIBWBCLIENT
	std::ostream & WinbindException::Write(std::ostream &stream) 
	{
		return stream << call << ": " << wbcErrorString(static_cast<wbcErr>(code)) << std::endl;
	}
#endif
	
	// 
	// Globally shared instance:
	// 
	Network * Network::Instance = 0;

	const Network * Network::GetInstance()
	{
		if(!Network::Instance) {
			Network::Instance = new Network();
		}
		return Network::Instance;
	}
	
	Network::Network()
	{
		ifreq req;
		const char *call;
		char *name = 0;
		int code;

		// 
		// Get MAC address for default route interface:
		// 
		if(get_default_route_iface(&req, &call, &code) < 0) {
			throw NetworkException(call, code);
		} else {
			char buff[18];
			const char *bytes = get_mac_addr(&req)->sa_data;
			snprintf(buff, sizeof(buff), "%02X:%02X:%02X:%02X:%02X:%02X",
				 bytes[0] & 0xff, bytes[1] & 0xff, bytes[2] & 0xff, bytes[3] & 0xff, bytes[4] & 0xff, bytes[5] & 0xff);
			hwaddr = buff;
		}
		
#ifdef HAVE_LIBWBCLIENT
		// 
		// Now resolve the NetBIOS name:
		// 
		if((code = wbcResolveWinsByIP("127.0.0.1", &name)) != WBC_ERR_SUCCESS) {
			throw WinbindException("wbcResolveWinsByIP", code);
		} else {
			// 
			// The returned string is 'ipaddr netbios'.
			// 
			std::string::size_type pos;
			computer = name;
			if((pos = computer.find('\t')) != std::string::npos) {
				while(isspace(computer[pos])) ++pos;
				computer = computer.substr(pos);
			}
			if((pos = computer.find('\n')) != std::string::npos) {
				computer = computer.substr(0, pos);
			}
			wbcFreeMemory(name);
		}
#else
		// 
		// Fake NetBIOS name by using upper case hostname.
		// 
		char buff[255];
		hostent *ent;
		
		if(gethostname(buff, sizeof(buff)) < 0) {
			throw NetworkException("gethostname");
		}
		if(!(ent = gethostbyname(buff))) {
			throw NetworkException("gethostbyname");
		}
		
		if(*(ent->h_aliases)) {
			strcpy(buff, *ent->h_aliases);   // use first
		} else {
			char *ps = strchr(buff, '.');    // fake alias
			if(ps) *ps = '\0';
		}
		for(int i = 0; i < strlen(buff); ++i) {
			buff[i] = toupper(buff[i]);
		}
		computer = buff;
#endif		
	}
	
}       // namespace WhosOn

#ifdef __LIBWHOSON_HAS_MAIN__
// 
// Compile: g++ -Wall -O -g -I../.. -DHAVE_CONFIG_H=1 -D__LIBWHOSON_HAS_MAIN__=1 network.cpp -o network .libs/libwhoson.so -Wl,-rpath=.libs
// 
#include <iostream>
int main()
{
	try {
		const WhosOn::Network *net = WhosOn::Network::GetInstance();
		std::cout 
			<< "Network:\n"
			<< "-----------------------\n"
			<< "   Computer: " << net->GetComputer() << "\n"
			<< "MAC address: " << net->GetMacAddress() << "\n"; 
	} catch(WhosOn::NetworkException exception) {
		exception.Write(std::cerr);
	}
	return 0;
}
#endif
