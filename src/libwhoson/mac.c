#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#ifdef HAVE_INTTYPES_H
# include <inttypes.h>
#endif
#ifdef HAVE_ARPA_INET_H
# include <arpa/inet.h>
#endif
#include <net/if.h>
#ifdef HAVE_SYS_IOCTL_H
# include <sys/ioctl.h>
#endif
#ifdef HAVE_SYS_SOCKET_H
# include <sys/socket.h>
#endif
#ifdef HAVE_CSTDLIB
# include <cstdlib>
#elif  HAVE_STDLIB_H
# include <stdlib.h>
#endif
#ifdef HAVE_UNISTD_H
# include <unistd.h>
#endif
#include <netinet/in.h>
#include <stdio.h>
#ifdef HAVE_STRING_H
# include <string.h>
#elif  HAVE_STRINGS_H
# include <strings.h>
#endif
#include <errno.h>

#define ARPHRD_ETHER 1

#define PROC_ROUTE "/proc/net/route"
#define BUFF_SIZE 200
#define DUMMY_MAC "\x00\x11\x22\x33\x44\x55"

#define set_last_error(func) { *call = func; *code = errno; }

/**
 * Get MAC address of the default route interface. The interface name and
 * MAC address is set in the req structure on return.
 * 
 * Returns -1 on error, setting the failed call and code to errno.
 */
int get_default_route_iface(struct ifreq *req, const char **call, int *code)
{	
#if defined(__APPLE__)
#endif // defined(__APPLE__)
#if defined(__linux__) 
	FILE *route;
	char buff[BUFF_SIZE];
	uint32_t dest = -1;
	int sock, res;
	
	if(!(route = fopen(PROC_ROUTE, "r"))) {
		set_last_error("fopen");
		return -1;
	}

	while(dest && fgets(buff, BUFF_SIZE, route)) {
		sscanf(buff, "%s %8" SCNx32, req->ifr_name, &dest);
	}
	fclose(route);
	
	if(dest) {
		set_last_error("gets");
		return -1;
	}

	req->ifr_hwaddr.sa_family = ARPHRD_ETHER;
	strcpy(req->ifr_hwaddr.sa_data, DUMMY_MAC);
	
	if((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		set_last_error("socket");
		return -1;
	}
	
	if(ioctl(sock, SIOCGIFHWADDR, req) < 0) {
		set_last_error("ioctl");
		return -1;
	}
	
	close(sock);
#endif  // defined(__linux__) 

	return 0;
}

/**
 * Get interface name from req structure.
 */
const char * get_iface_name(const struct ifreq *req)
{
	return req->ifr_name;
}

/**
 * Get MAC address from req structure.
 */
const struct sockaddr * get_mac_addr(const struct ifreq *req)
{
#if defined(__linux__) 
	return &req->ifr_hwaddr;
#endif
}
