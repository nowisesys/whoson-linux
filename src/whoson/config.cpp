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

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "config.hpp"

namespace {
	const char *ws = "\"' \t";     // Strip these characters
	
	inline std::string & ltrim(std::string &s, std::size_t pos = 0) {
		if((pos = s.find_first_not_of(ws)) != std::string::npos) {
			s = s.substr(pos);
		}
		return s;
	}
	
	inline std::string & rtrim(std::string &s, std::size_t pos = 0) {
	        if((pos = s.find_last_not_of(ws)) != std::string::npos) {
			s = s.substr(0, pos + 1);
		}
		return s;
	}
	
	inline std::string & trim(std::string &s) {
		return rtrim(ltrim(s));
	}
}

bool Config::Entry::Accept(const std::string &input)
{
	if(input[0] == Comment) {
		return false;
	}
	return input.find(Separator) != std::string::npos;
}

void Config::Entry::SetData(const std::string &input) 
{
	std::size_t pos = input.find(Separator);
	key = input.substr(0, pos);
	val = input.substr(pos + 1);
	
	val = trim(val);
}

Config::Iterator & Config::Iterator::operator++()
{
	entry = config->Next();
	return *this;
}

Config::Iterator Config::Iterator::operator++(int)
{
	Iterator tmp(*this);
	operator++();
	return tmp;
}

bool Config::Iterator::operator==(const Config::Iterator &i) const
{
	return entry == i.entry;
}

bool Config::Iterator::operator!=(const Config::Iterator &i) const
{
	return entry != i.entry;
}

Config::Config(const char *file) : stream(file)
{
}

Config::~Config()
{	
	stream.close();
}

const Config::Entry * Config::Current()
{
	return &entry;
}

const Config::Entry * Config::First()
{
	stream.clear();
	stream.seekg(0);
	return Next();
}

const Config::Entry * Config::Next()
{
	std::string line;
	
	while(stream.good()) {
		std::getline(stream, line);
		if(entry.Accept(line)) {
			entry.SetData(line);
			return &entry;
		}
	}
	return 0;
}

Config::Iterator Config::Begin() 
{ 
	First();
	return Iterator(this); 
}

Config::Iterator Config::End() 
{ 
	return Iterator(0); 
}
