#pragma once
#include <Windows.h>
#include <string>

class File
{
	std::string fileName;
	HANDLE file;
public:
	File(const char* fileName);
	bool Open();
	const char* GetString();
	~File();
};

