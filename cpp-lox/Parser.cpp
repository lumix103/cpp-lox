#include "Parser.h"

lox::Parser::Parser(std::deque<Token> tokens) : tokens(tokens)
{
}

lox::ExprPtr lox::Parser::parse()
{
	try {
		return expression();
	}
	catch (const ParseError& error) {
		return nullptr;
	}
}

lox::ExprPtr lox::Parser::expression()
{
	return equality();
}

lox::ExprPtr lox::Parser::equality()
{
	ExprPtr expr = std::move(comparison());
	while (match({ lox::BANG_EQUAL, lox::EQUAL_EQUAL })) {
		lox::Token op = previous();
		lox::ExprPtr right = std::move(comparison());
		expr = std::make_unique<Expression*>(new lox::Binary(std::move(expr), op, std::move(right)));
	}

	return expr;
}

lox::ExprPtr lox::Parser::comparison()
{
	lox::ExprPtr expr = addition();
	while (match({ lox::GREATER, lox::GREATER_EQUAL, lox::LESS,lox::LESS_EQUAL })) {
		Token op = previous();
		lox::ExprPtr right = std::move(addition());
		expr = std::make_unique<Expression*>(new lox::Binary(std::move(expr), op, std::move(right)));
	}
	return expr;
}

lox::ExprPtr lox::Parser::addition()
{
	lox::ExprPtr expr = std::move(multiplcation());
	while (match({ lox::MINUS, lox::PLUS })) {
		Token op = previous();
		lox::ExprPtr right = std::move(multiplcation());
		expr = std::make_unique<Expression*>(new lox::Binary(std::move(expr), op, std::move(right)));
	}
	return expr;
}

lox::ExprPtr lox::Parser::multiplcation()
{
	lox::ExprPtr expr = std::move(unary());
	while (match({ lox::SLASH, lox::STAR })) {
		lox::Token op = previous();
		lox::ExprPtr right = std::move(unary());
		expr = std::make_unique<lox::Expression*>(new lox::Binary(std::move(expr), op, std::move(right)));
	}
	return expr;
}

lox::ExprPtr lox::Parser::unary()
{
	if (match({ lox::BANG, lox::MINUS })) {
		lox::Token op = previous();
		lox::ExprPtr right = std::move(unary());
		lox::ExprPtr expr = std::make_unique<lox::Expression*>(new lox::Unary(op, std::move(right)));
		return expr;
	}
	return primary();
}

lox::ExprPtr lox::Parser::primary()
{
	if (match({ lox::FALSE, lox::TRUE, lox::NIL })) return std::make_unique<Expression*>(new lox::Literal(previous()));
	if (match({ lox::NUMBER, lox::STRING })) return std::make_unique<Expression*>(new lox::Literal(previous()));

	if (match({ lox::LEFT_PAREN })) {
		lox::ExprPtr expr = std::move(expression());
		consume(lox::RIGHT_PAREN, "Expect \')\' after expression.");
		lox::ExprPtr expr_1 = std::make_unique<Expression*>(new lox::Grouping(std::move(expr)));
		return expr_1;
	}

	throw error(peek(), "Expect expression.");
	return nullptr;
}

lox::Token lox::Parser::consume(TokenType type, std::string message)
{
	if (check(type)) return advance();
	throw error(peek(), message);
}

lox::ParseError lox::Parser::error(Token token, std::string message)
{
	lox::error(token, message.c_str());
	return ParseError();
}

lox::Token lox::Parser::advance()
{
	if (!isAtEnd()) current++;
	return previous();
}

lox::Token lox::Parser::peek()
{
	return tokens.at(current);
}

lox::Token lox::Parser::previous()
{
	return tokens.at(current - 1);
}

bool lox::Parser::match(std::list<lox::TokenType> types)
{
	for (auto type : types) {
		if (check(type)) {
			advance();
			return true;
		}
	}
	return false;
}

bool lox::Parser::check(lox::TokenType type)
{
	if (isAtEnd()) return false;
	return peek().type == type;
}

bool lox::Parser::isAtEnd()
{
	return peek().type == lox::END_OF_FILE;
}

void lox::Parser::synchronize()
{
	advance();
	while (!isAtEnd()) {
		if (previous().type == lox::SEMICOLON) return;
		switch (peek().type) {
		case lox::CLASS:
		case lox::FUN:
		case lox::VAR:
		case lox::FOR:
		case lox::IF:
		case lox::WHILE:
		case lox::PRINT:
		case lox::RETURN:
			return;
		}
	}
	advance();
}
