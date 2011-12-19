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
