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

#ifndef __CONFIG_HPP__
#define __CONFIG_HPP__

#include <string>
#include <fstream>

#include "whoson.hpp"

// 
// Class for reading configuration files. Note that this class keeps an 
// I/O stream opened during its lifetime. This has some effects on how
// the iterator is implemented and functions (C++ streams can't be cloned).
// 
class Config
{
public:

	// 
	// Representation of an configuration file entry.
	// 
	struct Entry 
	{
		enum { Separator = '=', Comment = '#' };
		
		std::string key;
		std::string val;

		bool Accept(const std::string &input);   // Accept input
		void SetData(const std::string &input);  // Split data
	};

	// 
	// Iterator utility class.
	// 
	struct Iterator
	{
		Iterator(Config *config) : config(config) { entry = config ? config->Current() : 0; }
		
		Iterator & operator++();
		Iterator operator++(int);
		
		bool operator==(const Iterator &i) const;
		bool operator!=(const Iterator &i) const;
		
		const Config::Entry & operator*() const { return *entry; }   // (*i).val
		const Config::Entry * operator->() const { return entry; }   // i->val
		
	private:
		Config *config;
		const Config::Entry *entry;
	};
	
	Config(const char *file);
	~Config();
	
	const Entry * First();
	const Entry * Next();
	const Entry * Current();
	
	Iterator Begin();
	Iterator End();
	
private:
	std::ifstream stream;
	Entry entry;
};

#endif // __CONFIG_HPP__
