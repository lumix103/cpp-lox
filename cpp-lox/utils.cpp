#include "utils.h"
#include <iostream>
#include <string>
void lox::error(int line, const char* message) {
	lox::report(line, "", message);
}

void lox::error(Token token, const char* message)
{
	if (token.type == TokenType::END_OF_FILE) {
		report(token.line, " at end", message);
	}
	else {
		std::string str = " at \'";
		str.append(token.lexeme);
		str.push_back('\'');
		report(token.line, str.c_str(), message);
	}
}

void lox::report(int line, const char* where, const char* message) {
	std::cout << "[Line: " << line << "] Where " << where
		<< ":" << message << "\n";
	hadError = true;
}

void lox::runtimeError(RuntimeError error)
{
	std::cout << error.what() << "\n[line " << error.op.line << "]" << std::endl;
	hadRuntimeError = true;
}

lox::RuntimeError::RuntimeError(Token op, std::string message) : op(op), messgae(message)
{
}

const char* lox::RuntimeError::what() const throw()
{
	return messgae.c_str();
}
