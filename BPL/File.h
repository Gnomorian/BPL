#pragma once
#include <Windows.h>

class File
{
	const char* fileName;
	HANDLE file;
public:
	File(const char* fileName);
	bool Open();
	const char* GetString();
	~File();
};

