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

#include <csignal>
#include <syslog.h>

// 
// Use prctl(2) on Linux. For other OS:es, fall back on using poll.
// 
#if defined(__linux__)
# include <sys/prctl.h>
# define PPID_POLL_INT 60
#else
# define PPID_POLL_INT 1
#endif

#include "whoson.hpp"     // library
#include "options.hpp"
#include "session.hpp"

void Session::Exception::Write() const
{
	if(code) {
		syslog(LOG_ERR, "Call to %s failed: %s (errno=%d)", call, strerror(code), code);
	} else {
		syslog(LOG_ERR, "Call to %s failed", call);
	}
}

volatile bool Session::done = false;

Session::Session(const WhosOn::LogonEventAdapter *adapter, Options *opts)
: adapter(adapter), opts(opts) 
{
	openlog(PACKAGE_NAME, LOG_PID | LOG_CONS, LOG_DAEMON);
}

Session::~Session()
{
	closelog();
}

void Session::Setup()
{
	sigset_t sigset;
	
	if(sigfillset(&sigset) < 0) {
		throw Exception("sigfillset");
	}
	if(sigdelset(&sigset, SIGTERM) < 0 ||
	   sigdelset(&sigset, SIGHUP)  < 0) {
		throw Exception("sigdelset");
	}
	if(sigprocmask(SIG_SETMASK, &sigset, 0) < 0) {
		throw Exception("sigprocmask");
	}
	
	if((signal(SIGTERM, SignalHandler) == SIG_ERR) ||
	   (signal(SIGHUP,  SignalHandler) == SIG_ERR)) {
		throw Exception("signal");
	}

#if defined(__linux__)
	if(prctl(PR_SET_PDEATHSIG, SIGTERM) < 0 ||
	   prctl(PR_SET_PDEATHSIG, SIGHUP)  < 0) {
		throw Exception("prctl", errno);
	}
#endif
}

void Session::Start()
{
	int event = adapter->Add();
	syslog(LOG_INFO, "Session started (event ID=%d)", event);
	
	while(!done) {
#if ! defined(__linux__)
		if(getppid() == 1) {
			syslog(LOG_INFO, "Parent PID = %d indicates adoption by init (time to exit)", getppid());
			break;
		}
#endif
		sleep(PPID_POLL_INT);
	}
	
	adapter->Close(event);
	syslog(LOG_INFO, "Session closed (event ID=%d)", event);
}

void Session::SignalHandler(int sig)
{
	if(sig == SIGTERM || sig == SIGHUP) {
		syslog(LOG_INFO, "Received signal %d, asking main loop to exit", sig);
		Done();
	}
}
