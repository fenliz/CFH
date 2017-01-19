#pragma once

#include <iostream>
#include <string>

namespace CFH
{
	// Base class for outputting messages written to the logger.
	class LogOutput
	{
	public:
		LogOutput() { }

		virtual void Write(const std::string& text) const {};
	};

	// Simple logoutput class that logs to the console.
	class ConsoleLogOutput : public LogOutput
	{
	public:
		ConsoleLogOutput() { }

		virtual void Write(const std::string& message) const
		{
			std::cout << message << std::endl;
		}
	};
}