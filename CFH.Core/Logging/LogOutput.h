#pragma once
#include "CFH.Core\Types.h"

#include <iostream>
#include <string>

namespace CFH
{
	// Base class for outputting messages written to the logger.
	class LogOutput
	{
	public:
		LogOutput() { }

		virtual void Write(const std::string& text, const std::string& timestamp,
						   const std::string& function, const std::string& filename, int line) const {};
	};

	// Simple logoutput class that logs to the console.
	class ConsoleLogOutput : public LogOutput
	{
	public:
		ConsoleLogOutput() { }

		virtual void Write(const std::string& message, const std::string& timestamp,
						   const std::string& function, const std::string& file, int line) const override
		{
			std::cout 
				//<< "[" << timestamp << "]" << "(" <<
				//function << "|" << file << "|" << line << ")"
				<< message << std::endl;
		}
	};
}