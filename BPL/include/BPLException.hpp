#pragma once
#include <exception>
class BPLException : public std::exception
{
	const char* message;
	const char* fileName;
	const char* function;
	int line;
	int errorCode;
	char buffer[1024];
public:
	BPLException(const char* message, const char* filename, const char* function, int line, int errorCode) noexcept;
	~BPLException();
	virtual char const* what() const;
};

