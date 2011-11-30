#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#ifdef HAVE_STRING_H
# include <string.h>
#elif  HAVE_STRINGS_H
# include <strings.h>
#endif
#ifdef HAVE_SYS_TYPES_H
# include <sys/types.h>
#endif
#include <pwd.h>

#include "account.hpp"

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
		struct passwd *pw = getpwuid(geteuid());
		if(pw) {
			char *seps = "/%\\|@";
			char *pu = pw->pw_name, *pd;
			
			if((pd = strpbrk(pu, seps))) {
				*pd++ = '\0';
			}
			
			user   = pu;
			domain = pd;
		}		
	}
	
}       // namespace WhosOn
