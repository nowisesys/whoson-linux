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
