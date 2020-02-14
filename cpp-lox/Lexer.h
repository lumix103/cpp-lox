#ifndef LEXER_H
#define LEXER_H

#include "Token.h"
#include <string>
#include <deque>

namespace lox {
	class Lexer {
	public:
		Lexer(std::string input);
		std::deque<lox::Token> scanTokens();
	private:
		void scanToken();
		bool isAtEnd();
		bool match(char c);
		char advance();
		char peek();
		char peekNext();
		void addToken(TokenType type);
		void addToken(TokenType type, std::string literal);
		void string();
		void number();
		void identifier();
		void comment();
	private:
		std::string input;
		int line;
		int start = 0;
		int current = 0;
		std::deque<lox::Token> tokens;
	};
}

#endif // !LEXER_H
