#pragma once

typedef enum token_type { T_WHITESPACE, T_IDENTIFIER, T_OPEN_PARENTH, T_CLOSED_PARENTH, T_CONSTANT, T_SEMICOLON, T_OPEN_BRACE, T_CLOSED_BRACE, T_KEYWORD };
static const char* TOKEN_NAME[] = {
	"whitespace",
	"identifier",
	"open_parenthesis",
	"closed_parenthesis",
	"constant",
	"semicolon",
	"open_brace",
	"closed_brace",
	"keyword"
};

static const char* KEYWORDS[] = {
	"int",
	"return",
	0
};

typedef struct token
{
	int type;		// the type of token, bracket, identifier, constant etc
	char* valuePos; // position of the token in the source string
	int optValueLen;// length of the optional value
}token;

class Lex
{
public:
	Lex();
	~Lex();
	// get a null terminated list of tokens in the given source file.
	token** lex_getTokens(const char* source);
	void lex_dumpTokens(token** tokens, bool printWhitespace);
private:
	token* GetNextToken(char** source);
	// find an identifier and create it as a token
	int FindIdentifier(char* source, token** tokn);
	// find a string of whitespace characters and create it as a token
	int FindSpace(char* source, token** tokn);
	// check if we have found an integer constant and add it as a token
	int FindConstant(const char* source, token** tokn);
	int FindPunctuation(const char* source, token** tokn);
	// checks if a found token is a known keyword
	int IsIdentifierKeyword(token* tokn);
	int IsValidIdentifierChar(char c, bool isFirstChar = false);
};

