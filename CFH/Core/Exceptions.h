#pragma once

#include <string>
#include <exception>

namespace CFH
{
	class Exception : public std::exception
	{
	public:
		const char* Message;

		Exception(const char* message) { Message = message; }
		~Exception() = default;
		const char* what() const throw() { return Message; }
	};

	class NotImplementedException final : public Exception
	{
	public:
		NotImplementedException() : Exception("Missing implementation!") {}
		NotImplementedException(const char* message) : Exception(message) {};
		NotImplementedException() = default;
	};

	class IndexOutOfRangeException final : public Exception
	{
		IndexOutOfRangeException() : Exception("Index was out of range!") {}
		IndexOutOfRangeException(const char* message) : Exception(message) {};
		IndexOutOfRangeException() = default;
	};
}