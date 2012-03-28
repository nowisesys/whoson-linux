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

#ifndef __OUTPUT_HPP__
#define __OUTPUT_HPP__

#include <vector>
#include <string>
#include "whoson.hpp"

class IOutputFormat
{
public:
	virtual void WriteHeader() const = 0;
	virtual void WriteFooter(const std::vector<WhosOn::LogonEvent *> *records) const = 0;
	virtual void WriteRecord(const WhosOn::LogonEvent *record) const = 0;
};

class OutputFormatHuman : public IOutputFormat
{
private:
	static std::string Separator;
	
public:
	void WriteHeader() const;
	void WriteFooter(const std::vector<WhosOn::LogonEvent *> *records) const;
	void WriteRecord(const WhosOn::LogonEvent *record) const;
};

class OutputFormatTabbed : public IOutputFormat
{
public:
	void WriteHeader() const;
	void WriteFooter(const std::vector<WhosOn::LogonEvent *> *records) const;
	void WriteRecord(const WhosOn::LogonEvent *record) const;
};

class OutputFormatCompact : public IOutputFormat
{
public:
	void WriteHeader() const;
	void WriteFooter(const std::vector<WhosOn::LogonEvent *> *records) const;
	void WriteRecord(const WhosOn::LogonEvent *record) const;
};

class OutputFormatXML : public IOutputFormat
{
public:
	void WriteHeader() const;
	void WriteFooter(const std::vector<WhosOn::LogonEvent *> *records) const;
	void WriteRecord(const WhosOn::LogonEvent *record) const;
};

class ProgramOutput
{
public:
	void SetFormat(IOutputFormat *format);
	void Write(const std::vector<WhosOn::LogonEvent *> *records) const;
private:
	IOutputFormat *format;
};

#endif  // __OUTPUT_HPP__
