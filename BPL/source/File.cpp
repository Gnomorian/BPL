#include "File.hpp"
#include "BPLException.hpp"
#include <string>

File::File(const char* fileName)
{
	char buffer[256] = { 0 };
	GetCurrentDirectory(256, buffer);
	this->fileName = buffer;
	this->fileName += "\\";
	this->fileName += fileName;
	file = nullptr;
}


File::~File()
{

}

bool File::Open()
{
	// open the file
	file = CreateFile(fileName.c_str(), GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (file == INVALID_HANDLE_VALUE)
	{
		DWORD result = GetLastError();
		char msg[256] = { 0 };
		sprintf_s(msg, "Cant open file '%s'", fileName.c_str());
		throw BPLException(msg, __FILE__, __FUNCTION__, __LINE__, result);
		return false;
	}
	return true;
}

const char* File::GetString()
{
	if (file == nullptr)
		Open();

	// get the length of the file and allocate a suitable buffer
	long length = GetFileSize(file, 0);
	char* buffer = (char*)malloc(length + 1 * sizeof(char));
	buffer[length / sizeof(char)] = 0;

	// read the contents of the file
	if (!ReadFile(file, buffer, length, 0, 0))
	{
		DWORD result = GetLastError();
		char msg[256] = { 0 };
		sprintf_s(msg, "Cant read file '%s'", fileName);
		throw BPLException(msg, __FILE__, __FUNCTION__, __LINE__, result);
	}

	return buffer;
}