// WhosOn Linux - Centralized Logon Accounting (WhosOn Program Suite).
// 
// Copyright (C) 2011-2018 Anders Lövgren, BMC-IT, Uppsala University.
// Copyright (C) 2018-2019 Anders Lövgren, Nowise Systems.
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

#ifndef __LIBWHOSON_NETWORK_HPP__
#define __LIBWHOSON_NETWORK_HPP__

#include <string>
#include <iostream>

#ifdef HAVE_STRING_H
# include <string.h>
#elif  HAVE_STRINGS_H
# include <strings.h>
#endif
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
