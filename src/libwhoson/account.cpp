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

#include <vector>
#ifdef HAVE_STRING_H
# include <string.h>
#elif  HAVE_STRINGS_H
# include <strings.h>
#endif
#ifdef HAVE_SYS_TYPES_H
# include <sys/types.h>
#endif
#include <pwd.h>

#ifdef HAVE_KRB5_H
extern "C" {
# include <krb5.h>
}
#endif

#ifndef HAVE_COM_ERR
void com_err(const char *, long, const char *, ...) {}
#endif

#include "account.hpp"

namespace {
	
	using namespace WhosOn;
	
#ifdef HAVE_LIBKRB5
	class KerberosAccount : public AccountProvider
	{
	public:
	
		KerberosAccount()
		{
			flags = 0;   // turns off OPENCLOSE mode
			cache = 0;
		}
		
		~KerberosAccount() 
		{
			krb5_free_context(context);
		}
		
		std::string GetName() const 
		{
			return "Kerberos V5";
		}
		
		void Lookup() 
		{
			const char *name = 0, *prog = "";
			char *pnam, *pdom;
			
			if((code = krb5_init_context(&context))) {
				com_err(prog, code, "failed initialize context");
				throw AccountProvider::Exception();
			}
			
			if(!name) {
				if((code = krb5_cc_default(context, &cache))) {
					com_err(prog, code, "failed getting default ccache");
					throw AccountProvider::Exception();
				}
			} else {
				if ((code = krb5_cc_resolve(context, name, &cache))) {
					com_err(prog, code, "failed resolving ccache %s", name);
					throw AccountProvider::Exception();
				}
			}
			
			if((code = krb5_cc_set_flags(context, cache, flags))) {
				com_err(prog, code,
					"failed set cache flags (ticket cache %s:%s)",
					krb5_cc_get_type(context, cache),
					krb5_cc_get_name(context, cache));
				throw AccountProvider::Exception();
			}
			if((code = krb5_cc_get_principal(context, cache, &princ))) {
				com_err(prog, code, "failed retrieving principal name");
				throw AccountProvider::Exception();
			}
			if((code = krb5_unparse_name(context, princ, &pnam))) {
				com_err(prog, code, "failed unparsing principal name");
				throw AccountProvider::Exception();
			}
			
			if((pdom = strchr(pnam, '@'))) {
				*pdom++ = '\0';
			} else {
				com_err(prog, 0, "failed match '@' in principal name");
				throw AccountProvider::Exception();
			}
			
			user   = pnam;
			domain = pdom;
		}
	private:
		krb5_error_code code;
		krb5_context context;
		krb5_ccache cache;
		krb5_flags flags;
		krb5_principal princ;
	};
	
#endif  // HAVE_LIBKRB5
	
	class SystemAccount : public AccountProvider
	{
	public:
		std::string GetName() const 
		{
			return "System DB/NSS";
		}
		
		void Lookup() 
		{
			struct passwd *pw = getpwuid(geteuid());
			if(!pw) {
				throw AccountProvider::Exception();
			}
			
			const char *seps = "/%\\|@";
			char *pu = pw->pw_name, *pd;
				
			if((pd = strpbrk(pu, seps))) {
				*pd++ = '\0';
			}
			
			if(pd) {
				user   = pu;
				domain = pd;
			} else {
				user   = pu;
			}
		}
	};

	// 
	// Just in case ;-)
	// 
	class DefaultProvider : public AccountProvider
	{
	public:
		void Lookup() {}
		std::string GetName() const { return "Default"; }
	};

}       // namespace

namespace WhosOn {
		
	// 
	// Globally shared instance:
	// 
	Account * Account::Instance = 0;

	const Account * Account::GetInstance()
	{
		if(!Account::Instance) {
			Account::Instance = new Account();
		}
		return Account::Instance;
	}

	// 
	// Try to figure out the username and domain from system password 
	// database. In spite of the manual page found on some systems, the
	// getpwuid() call should return entries from external sources as
	// LDAP or Samba.
	// 
	Account::Account()
	{
		
#ifdef HAVE_LIBKRB5
		providers.push_back(new KerberosAccount());
#endif 
		providers.push_back(new SystemAccount());
		providers.push_back(new DefaultProvider());
		
		for(Iterator it = providers.begin(); it != providers.end(); ++it) {
			try {
				selected = *it;
				selected->Lookup();
			} catch(AccountProvider::Exception) {
				continue;
			}
			break;   // we are done!
		}
	}
	
	Account::~Account()
	{
		for(Iterator it = providers.begin(); it != providers.end(); ++it) {
			delete *it;
		}
	}
	
}       // namespace WhosOn

#ifdef __LIBWHOSON_HAS_MAIN__
// 
// Compile: g++ -Wall -O -g -I../.. -DHAVE_CONFIG_H=1 -D__LIBWHOSON_HAS_MAIN__=1 account.cpp -o account .libs/libwhoson.so -Wl,-rpath=.libs
// 
#include <iostream>
int main()
{	
	const WhosOn::Account *acc = WhosOn::Account::GetInstance();
	
	const std::vector<AccountProvider *> * providers = acc->GetProviders();
	typedef WhosOn::Account::Iterator Iterator;
	std::cout << "Providers:\n";
	for(Iterator it = providers->begin(); it != providers->end(); ++it) {
		AccountProvider *provider = *it;
		std::cout << "  Name: " << provider->GetName() << std::endl;
	}
	std::cout << "  Selected: " << acc->GetProvider()->GetName() << std::endl << std::endl;
	
	std::cout 
		<< "Account:\n"
		<< "-----------------------\n"
		<< "   Username: " << acc->GetUsername() << "\n"
		<< "     Domain: " << acc->GetDomain() << "\n"; 
	return 0;
}
#endif
