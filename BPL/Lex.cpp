#include "Lex.h"
#include <iostream>


Lex::Lex()
{
}


Lex::~Lex()
{
}

token* Lex::GetNextToken(char** source)
{
	token* tokn = 0;
	if (*source == 0)
		return 0;
	if (FindSpace(*source, &tokn))
	{
		goto end;
	}
	if (FindIdentifier(*source, &tokn))
	{
		if (IsIdentifierKeyword(tokn))
			tokn->type = T_KEYWORD;
		goto end;
	}
	if (FindConstant(*source, &tokn))
	{
		goto end;
	}
	if (FindPunctuation(*source, &tokn))
	{
		goto end;
	}
	return 0;
end:
	*source += tokn->optValueLen;
	return tokn;
}

token** Lex::lex_getTokens(const char* source)
{
	// TODO: replace this with a vector, when you make one.
	token* tokens[1000] = { 0 };
	int tokensArrayPos = 0;
	char* current = (char*)source;
	token* newestToken = 0;

	// fill tokens array with the next token until it returns null
	do {
		if (newestToken)
			tokens[tokensArrayPos++] = newestToken;
		newestToken = GetNextToken(&current);
	} while (newestToken != 0);

	int length = 0;
	for (; tokens[length]; length++);
	if (length == 0)
		return 0;


	token * *t = (token**)malloc((length + 1) * sizeof(token*));
	memcpy(t, tokens, (length + 1) * sizeof(token*));

	return t;
}

void Lex::lex_dumpTokens(token * *tokens, bool printWhitespace)
{
	//TODO: change to use name for the int representation of the token
	for (int i = 0; tokens[i]; i++)
	{
		token* t = tokens[i];
		if (!printWhitespace && t->type == T_WHITESPACE)
		{
			printf("%i) type='%s'\n", i, TOKEN_NAME[t->type]);
		}
		else
			printf("%i) type='%s' value='%.*s'\n", i, TOKEN_NAME[t->type], t->optValueLen, t->valuePos);
	}
}

int Lex::FindSpace(char* source, token** tokn)
{
	char* end = source;

	if (isspace(*source))
	{
		// find the last space character in this sequence
		int length = 0;
		for (length; isspace(*end); length++) { ++end; }
		token* t = (token*)malloc(sizeof(token));
		t->type = T_WHITESPACE;
		t->valuePos = source;
		t->optValueLen = length;
		source = end;
		*tokn = t;
		return 1;
	}
}

int Lex::FindIdentifier(char* source, token** tokn)
{
	char* end = source;
	if (IsValidIdentifierChar(*source, 1))
	{
		int length = 0;
		for (length; IsValidIdentifierChar(*end); length++) { ++end; }
		token* t = (token*)malloc(sizeof(token));
		t->type = T_IDENTIFIER;
		t->valuePos = source;
		t->optValueLen = length;
		source = end;
		*tokn = t;
		return 1;
	}
	return 0;
}

int Lex::FindConstant(const char* source, token** tokn)
{
	//TODO: add handling for string constants
	char* end = (char*)source;

	if (isdigit(*source))
	{
		int length = 0;
		for (length; isdigit(*end); length++) { ++end; }
		token* t = (token*)malloc(sizeof(token));
		t->type = T_CONSTANT;
		t->valuePos = (char*)source;
		t->optValueLen = length;
		source = end;
		*tokn = t;
		return 1;
	}
	return 0;
}

int Lex::FindPunctuation(const char* source, token** tokn)
{
	int type = 0;
	switch (*source)
	{
	case '{':
		type = T_OPEN_PARENTH;
		break;
	case '}':
		type = T_CLOSED_PARENTH;
		break;
	case '(':
		type = T_OPEN_BRACE;
		break;
	case ')':
		type = T_CLOSED_BRACE;
		break;
	case ';':
		type = T_SEMICOLON;
		break;
	default:
		return 0;
	}
	token* t = (token*)malloc(sizeof(token));
	t->type = type;
	t->valuePos = (char*)source;
	t->optValueLen = 1;
	*tokn = t;
	return 1;
}

int Lex::IsIdentifierKeyword(token* tokn)
{
	for (int i = 0; KEYWORDS[i]; i++)
	{
		if (memcmp(KEYWORDS[i], tokn->valuePos, tokn->optValueLen))
		{
			return 1;
		}
	}
	return 0;
}

int Lex::IsValidIdentifierChar(char c, bool isFirstChar)
{
	// is it a letter?
	if (isupper(c) || islower(c))
	{
		return 1;
	}
	// are we checking the first character in a suspected identifier?
	else if (!isFirstChar)
	{
		// is it a number or a valid punctuation character?
		if (isdigit(c) || c == '_' || c == '-')
			return 1;
	}
	return 0;
}