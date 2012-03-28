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

#ifndef __SESSION_HPP__
#define __SESSION_HPP__

class Session
{
public:
	struct Exception
	{
		const char *call;
		int code;        // errno
		Exception(const char *call, int code = 0) : call(call), code(code) {}
		void Write() const;
	};
	
	Session(const WhosOn::LogonEventAdapter *adapter, Options *opts);
	~Session();
	
	void Setup();
	void Start();
	
	static void Done() { done = true; }
	static void SignalHandler(int sig);
	
private:
	const WhosOn::LogonEventAdapter *adapter;
	Options *opts;
	volatile static bool done;
};

#endif // __SESSION_HPP__
