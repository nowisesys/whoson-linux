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

#ifndef __LIBWHOSON_ACCOUNT_HPP__
#define __LIBWHOSON_ACCOUNT_HPP__

#include <string>
#include <vector>

namespace WhosOn {

	class AccountProvider
	{
	public:
		struct Exception {};
		
		virtual ~AccountProvider() {};
		virtual void Lookup() = 0;           // throws
		
		virtual std::string GetName() const = 0;
		const std::string & GetUser() const { return user; }
		const std::string & GetDomain() const { return domain; }

	protected:
		std::string user;
		std::string domain;    // empty for local logons
	};
	
	class Account
	{
	public:
		typedef std::vector<AccountProvider *>::const_iterator Iterator;
		
		static const Account * GetInstance();
		
		const std::vector<AccountProvider *> * GetProviders() const { return &providers; }
		const AccountProvider * GetProvider() const { return selected; }
		
		const std::string & GetUsername() const { return selected->GetUser(); }
		const std::string & GetDomain() const   { return selected->GetDomain(); }
		
	protected:
		Account();
		~Account();
		
		static Account * Instance;
		std::vector<AccountProvider *> providers;
		AccountProvider *selected;
	};
	
}       // namespace WhosOn

#endif  // __LIBWHOSON_ACCOUNT_HPP__
