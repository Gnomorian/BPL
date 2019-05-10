#include <cstdio>
#include "File.h"
#include "Lex.h"
#include "BPLException.h"

#define SOURCE_FILE "C:\\Users\\William\\source\\repos\\BCC\\Debug\\x64\\Bin\\main.bc"

int main(int argc, char* args[])
{
	File file(SOURCE_FILE);
	token** tokens = nullptr;
	try {
		const char* source = file.GetString();

		Lex lex;
		tokens = lex.lex_getTokens(source);
		lex.lex_dumpTokens(tokens, true);
	}
	catch (BPLException& e)
	{
		puts(e.what());
	}
	

	(void)getchar();
	// cleanup
	if (tokens == nullptr)
		return -1;
	for (int i = 0; tokens[i]; i++)
		free(tokens[i]);
}
