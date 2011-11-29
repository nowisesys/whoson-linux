#ifndef __LIBWHOSON_ACCOUNT_HPP__
#define __LIBWHOSON_ACCOUNT_HPP__

#include <string>

namespace WhosOn {

	class Account
	{
	public:
		static const Account * GetInstance();
		
		std::string GetUsername() const { return user; }
		std::string GetDomain() const { return domain; }
		
	protected:
		Account();
		static Account * Instance;
		
		std::string user;
		std::string domain;      // empty for local logons
	};
	
}       // namespace WhosOn

#endif  // __LIBWHOSON_ACCOUNT_HPP__
