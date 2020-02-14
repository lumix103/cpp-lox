#ifndef PARSER_H
#define PARSER_H

#include "Expression.h"
#include <deque>
#include "utils.h"
namespace lox {

	class ParseError : public std::exception {};

	class Parser {
	private:
		std::deque<Token> tokens;
		int current = 0;
	public:
		Parser(std::deque<Token> tokens);
		ExprPtr parse();
	private:
		ExprPtr expression();
		ExprPtr equality();
		ExprPtr comparison();
		ExprPtr addition();
		ExprPtr multiplcation();
		ExprPtr unary();
		ExprPtr primary();
		Token consume(TokenType type, std::string message);
		ParseError error(Token token, std::string message);
		Token advance();
		Token peek();
		Token previous();
		bool match(std::list<TokenType> types);
		bool check(TokenType type);
		bool isAtEnd();
		void synchronize();
	};
}


#endif //PARSER_H