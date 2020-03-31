#ifndef PARSER_H
#define PARSER_H

#include "Expression.h"
#include <deque>
#include "utils.h"
#include "Statement.h"
namespace lox {
	class Parser {
	private:
		std::deque<Token> tokens;
		int current = 0;
	public:
		Parser(std::deque<Token> tokens);
		//ExprPtr parse();
		std::deque<StmtPtr> parse();
	private:
		ExprPtr expression();
		ExprPtr assignement();
		ExprPtr _or();
		ExprPtr _and();
		ExprPtr equality();
		ExprPtr comparison();
		ExprPtr addition();
		ExprPtr multiplcation();
		ExprPtr call();
		ExprPtr finishCall(ExprPtr expr);
		ExprPtr unary();
		ExprPtr primary();
		StmtPtr declaration();
		StmtPtr varDeclaration();
		StmtPtr statement();
		StmtPtr forStatement();
		StmtPtr function(std::string kind);
		StmtPtr ifStatement();
		StmtPtr printStatement();
		StmtPtr whileStatement();
		StmtPtr expressionStatement();
		std::deque<StmtPtr> block();
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