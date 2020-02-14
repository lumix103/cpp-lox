#include "Token.h"
#include <iostream>
void lox::pretty_print_token(const Token token)
{
	std::cout << "Type: " << token.type << " [line: " << token.line << "] Lexeme: " << token.lexeme << std::endl;
}