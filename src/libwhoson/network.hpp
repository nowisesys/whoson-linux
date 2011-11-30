#ifndef __LIBWHOSON_NETWORK_HPP__
#define __LIBWHOSON_NETWORK_HPP__

#include <string>
#include <iostream>

#include <string.h>
#include <errno.h>

namespace WhosOn {
	
	struct NetworkException
	{
		const char *call;    // syscall
		int code;
		
		NetworkException(const char *call) : call(call), code(errno)  {}
		NetworkException(const char *call, int code) : call(call), code(code) {}
		virtual std::ostream & Write(std::ostream &stream) { return stream << call << ": " << strerror(code) << " (" << code << ")\n"; }
	};
	
	struct WinbindException : public NetworkException
	{
		WinbindException(const char *call, int code) : NetworkException(call, code) {}
		std::ostream & Write(std::ostream &stream);
	};
	
	class Network
	{
	public:
		static const Network * GetInstance();
		
		std::string GetComputer() const { return computer; }
		std::string GetMacAddress() const { return hwaddr; }
		
	protected:
		Network();
		static Network * Instance;
		
		std::string computer;
		std::string hwaddr;
	};
	
}       // namespace WhosOn

#endif  // __LIBWHOSON_NETWORK_HPP__
