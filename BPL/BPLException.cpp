#include "BPLException.h"
#include <ostream>
#include <strstream>


BPLException::BPLException(const char* message, const char* filename, const char* function, int line, int errorCode) noexcept
{
	this->message = message;
	this->fileName = filename;
	this->function = function;
	this->line = line;
	this->errorCode = errorCode;
	memset(buffer, 0, sizeof(buffer));
	sprintf_s(buffer, "[%d] \"%s\" %s::%s(%d)\n", errorCode, message, fileName, function, line);
}


BPLException::~BPLException()
{
	
}

char const* BPLException::what() const
{
	return buffer;
}