#include <cstdio>
#include "File.hpp"
#include "Lex.hpp"
#include "BPLException.hpp"

int main(int argc, char* args[])
{
	if (argc < 2)
	{
		puts("No source file in exe arguments");
		getchar();
		return -1;
	}

	File file(args[1]);

	try {
		const char* source = file.GetString();

		Lex lex;
		(void)lex.getTokens(source);
		lex.dumpTokens();
	}
	catch (BPLException& e)
	{
		puts(e.what());
	}
	

	(void)getchar();
}
