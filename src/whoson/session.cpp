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
		if(opts->Verbose) {
			syslog(LOG_INFO, "Received signal %d, asking main loop to exit", sig);
		}
		Done();
	}
}
