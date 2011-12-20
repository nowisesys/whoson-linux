#include <iostream>
#include "output.hpp"
#include "datetime.hpp"

std::string OutputFormatHuman::Separator = "-----------------------------------------------------";
		
void OutputFormatHuman::WriteHeader() const
{
	// ignore
}

void OutputFormatHuman::WriteFooter(const std::vector<WhosOn::LogonEvent *> *records) const
{
	std::cout << Separator << std::endl;
	std::cout << "Summary: " << records->size() << " records in output\n";
}

void OutputFormatHuman::WriteRecord(const WhosOn::LogonEvent *record) const
{
	std::cout 
		<< "User: " << record->Username << "\\" << record->Domain << "(Event ID=" << record->EventID << ")\n"
		<< Separator << std::endl
		<< "\t  Computer: " << record->Hostname << " (NetBIOS Name: " << record->Workstation << ")\n"
		<< "\tIP-address: " << record->IpAddress << " (MAC-address: " << record->HwAddress << ")\n";
	if(record->EndTime <= 0) {     // Less that the UNIX epoch
		std::cout << "\t   Session: " << DateTime(record->StartTime) << " -> [(still logged on)]\n";
	}
	else {
		std::cout << "\t   Session: " << DateTime(record->StartTime) << " -> " << DateTime(record->EndTime) << std::endl;
	}
	std::cout << std::endl;
}

void OutputFormatTabbed::WriteHeader() const
{
	std::cout << "Event ID:\tUsername:\tDomain:\tMAC:\tIP-address\tHostname:\tWorkstation (NetBIOS):\tStart:\tEnd:\n";
}

void OutputFormatTabbed::WriteFooter(const std::vector<WhosOn::LogonEvent *> *records) const
{
	// ignore
}
	
void OutputFormatTabbed::WriteRecord(const WhosOn::LogonEvent *record) const
{
	std::cout 
		<< record->EventID << "\t" 
		<< record->Domain << "\t"
		<< record->HwAddress << "\t"
		<< record->IpAddress << "\t"
		<< record->Hostname << "\t"
		<< record->Workstation << "\t"
		<< DateTime(record->StartTime) << "\t"
		<< DateTime(record->EndTime) << "\n";
}

void OutputFormatCompact::WriteHeader() const
{
	std::cout << "EventID: Username: Domain: MAC: IP-address Hostname: Workstation: Start: End:\n";
}
	
void OutputFormatCompact::WriteFooter(const std::vector<WhosOn::LogonEvent *> *records) const
{
	// ignore
}

void OutputFormatCompact::WriteRecord(const WhosOn::LogonEvent *record) const
{
	std::cout 
		<< record->EventID << " "
		<< record->Username << " "
		<< record->Domain << " "
		<< record->HwAddress << " "
		<< record->IpAddress << " "
		<< record->Hostname << " "
		<< record->Workstation << " "
		<< DateTime(record->StartTime) << " "
		<< DateTime(record->EndTime) << std::endl;
}

void OutputFormatXML::WriteHeader() const
{
	std::cout << "<?xml encoding='utf8' version='1.0' ?>\n";
	std::cout << "<LogonEvents>\n";
}
	
void OutputFormatXML::WriteFooter(const std::vector<WhosOn::LogonEvent *> *records) const
{
	std::cout << "</LogonEvents>\n";
}

void OutputFormatXML::WriteRecord(const WhosOn::LogonEvent *record) const
{
	std::cout 
		<< "  <LogonEvent ID=" << record->EventID << ">\n"
		<< "    <Logon>\n"
		<< "      <Username>" << record->Username << "</Username>\n"
		<< "      <Domain>" << record->Domain << "</Domain>\n"
		<< "    </Logon>\n"
		<< "    <Computer>\n"
		<< "      <HwAddress>" << record->HwAddress << "</HwAddress>\n"
		<< "      <IpAddress>" << record->IpAddress << "</IpAddress>\n"
		<< "      <Hostname>" << record->Hostname << "</Hostname>\n"
		<< "      <Workstation>" << record->Workstation << "</Workstation>\n"
		<< "    </Computer>\n"
		<< "    <Session>\n"
		<< "      <StartTime>" << DateTime(record->StartTime) << "</StartTime>\n"
		<< "      <EndTime>" << DateTime(record->EndTime) << "</EndTime>\n"
		<< "    </Session>\n"
		<< "  </LogonEvent>\n";
}

void ProgramOutput::SetFormat(IOutputFormat *format)
{
	this->format = format;
}

void ProgramOutput::Write(const std::vector<WhosOn::LogonEvent *> *records) const
{
	if(records->size() > 0)
	{
		typedef std::vector<WhosOn::LogonEvent *>::const_iterator Iterator;
		
		format->WriteHeader();
		for(Iterator it = records->begin(); it != records->end(); ++it) {
			format->WriteRecord(*it);
		}
		format->WriteFooter(records);
	}
}
