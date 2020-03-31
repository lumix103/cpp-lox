#include "Parser.h"

lox::Parser::Parser(std::deque<Token> tokens) : tokens(tokens)
{
}
/*
lox::ExprPtr lox::Parser::parse()
{
	try {
		return expression();
	}
	catch (const ParseError& error) {
		return nullptr;
	}
}
*/

std::deque<lox::StmtPtr> lox::Parser::parse() {
	std::deque<StmtPtr> statements;
	while (!isAtEnd()) {
		statements.push_back(declaration());
	}
	return statements;
}

lox::ExprPtr lox::Parser::expression()
{
	return assignement();
}

lox::ExprPtr lox::Parser::assignement()
{
	ExprPtr expr = _or();
	//ExprPtr expr = equality();
	if (match({EQUAL})) {
		Token equals = previous();
		ExprPtr value = assignement();
		IsA isA;
		if (isA(*expr) == EXPR_VARIABLE) {
			Token name;
			Variable* var = (Variable*)*expr;
			name = var->name;
			return std::make_shared<Expression*>(new Assign(name, value));
		}
		error(equals, "Invalid assignment target.");
	}
	return expr;
}

lox::ExprPtr lox::Parser::_or()
{
	ExprPtr expr = _and();
	while (match({ OR })) {
		Token op = previous();
		ExprPtr right = _and();
		expr = std::make_shared<Expression*>(new Logical(expr, op, right));
	}
	return expr;
}

lox::ExprPtr lox::Parser::_and()
{
	ExprPtr expr = equality();
	while (match({ AND })) {
		Token op = previous();
		ExprPtr right = equality();
		expr = std::make_shared<Expression*>(new Logical(expr, op, right));
	}
	return expr;
}

lox::ExprPtr lox::Parser::equality()
{
	ExprPtr expr = std::move(comparison());
	while (match({ lox::BANG_EQUAL, lox::EQUAL_EQUAL })) {
		lox::Token op = previous();
		lox::ExprPtr right = std::move(comparison());
		expr = std::make_shared<Expression*>(new lox::Binary(std::move(expr), op, std::move(right)));
	}

	return expr;
}

lox::ExprPtr lox::Parser::comparison()
{
	lox::ExprPtr expr = addition();
	while (match({ lox::GREATER, lox::GREATER_EQUAL, lox::LESS,lox::LESS_EQUAL })) {
		Token op = previous();
		lox::ExprPtr right = std::move(addition());
		expr = std::make_shared<Expression*>(new lox::Binary(std::move(expr), op, std::move(right)));
	}
	return expr;
}

lox::ExprPtr lox::Parser::addition()
{
	lox::ExprPtr expr = std::move(multiplcation());
	while (match({ lox::MINUS, lox::PLUS })) {
		Token op = previous();
		lox::ExprPtr right = std::move(multiplcation());
		expr = std::make_shared<Expression*>(new lox::Binary(std::move(expr), op, std::move(right)));
	}
	return expr;
}

lox::ExprPtr lox::Parser::multiplcation()
{
	lox::ExprPtr expr = std::move(unary());
	while (match({ lox::SLASH, lox::STAR })) {
		lox::Token op = previous();
		lox::ExprPtr right = std::move(unary());
		expr = std::make_shared<lox::Expression*>(new lox::Binary(std::move(expr), op, std::move(right)));
	}
	return expr;
}

lox::ExprPtr lox::Parser::call()
{
	ExprPtr expr = primary();
	while (true) {
		if (match({ LEFT_PAREN })) {
			expr = finishCall(expr);
		}
		else {
			break;
		}
	}

	return expr;
}

lox::ExprPtr lox::Parser::finishCall(lox::ExprPtr expr)
{
	std::deque<ExprPtr> args;
	if (!check(RIGHT_PAREN)) {
		do {
			if (args.size() >= 255)
			{
				error(peek(), "Cannot have more than 255 arguements");
			}
			args.push_back(expression());
		} while (match({ COMMA }));
	}
	Token paren = consume(RIGHT_PAREN, "Expect \')\' after arguements");
	return std::make_shared<Expression*>(new Call(expr, paren, args));
}

lox::ExprPtr lox::Parser::unary()
{
	if (match({ lox::BANG, lox::MINUS })) {
		lox::Token op = previous();
		lox::ExprPtr right = std::move(unary());
		lox::ExprPtr expr = std::make_shared<lox::Expression*>(new lox::Unary(op, std::move(right)));
		return expr;
	}
	return call();
}

lox::ExprPtr lox::Parser::primary()
{
	if (match({ lox::FALSE, lox::TRUE, lox::NIL })) return std::make_shared<Expression*>(new lox::Literal(previous()));
	if (match({ lox::NUMBER, lox::STRING })) return std::make_shared<Expression*>(new lox::Literal(previous()));
	if (match({ lox::IDENTIFIER })) {
		return std::make_shared<Expression*>(new Variable(previous()));
	}
	if (match({ lox::LEFT_PAREN })) {
		lox::ExprPtr expr = std::move(expression());
		consume(lox::RIGHT_PAREN, "Expect \')\' after expression.");
		lox::ExprPtr expr_1 = std::make_shared<Expression*>(new lox::Grouping(std::move(expr)));
		return expr_1;
	}

	throw error(peek(), "Expect expression.");
	return nullptr;
}

lox::StmtPtr lox::Parser::declaration()
{
	try {
		if (match({ FUN })) return function("function");
		if (match({ VAR }))
			return varDeclaration();
		return statement();
	}
	catch (const ParseError& e) {
		synchronize();
		return nullptr;
	}
	return nullptr;
}

lox::StmtPtr lox::Parser::varDeclaration()
{
	Token name = consume(IDENTIFIER, "Expeect variable name.");
	ExprPtr initializer = nullptr;
	if (match({ EQUAL })) {
		initializer = expression();
	}
	consume(SEMICOLON, "Expect \';\' after variable declaration.");
	return std::make_shared<Statement*>(new Var(name, initializer));
}

lox::StmtPtr lox::Parser::statement()
{
	if (match({ FOR })) return forStatement();
	if (match({ IF })) return ifStatement();
	if (match({ PRINT })) return printStatement();
	if (match({ WHILE })) return whileStatement();
	if (match({ LEFT_BRACE })) return std::make_shared<Statement*>(new Block(block()));
	return expressionStatement();
}

lox::StmtPtr lox::Parser::forStatement()
{
	consume(LEFT_PAREN, "Expect \'(\' after \'if\'.");
	StmtPtr initializer;
	if (match({ SEMICOLON })) {
		initializer = nullptr;
	}
	else if (match({ VAR })) {
		initializer = varDeclaration();
	}
	else {
		initializer = expressionStatement();
	}

	ExprPtr condition = nullptr;
	if (!check(SEMICOLON)) {
		condition = expression();
	}
	consume(SEMICOLON, "Expect \';\' after loop condition.");

	ExprPtr increment = nullptr;
	if (!check(RIGHT_PAREN)) {
		increment = expression();
	}
	consume(RIGHT_PAREN, "Expect \')\' after for clauses.");
	StmtPtr body = statement();

	if (increment != nullptr) {
		body = std::make_shared<Statement*>(new Block({ body, std::make_shared<Statement*>(new ExpressionStatement(increment)) }));
	}
	if (condition == nullptr) {
		Token token;
		token.value = "true";
		token.lexeme = "true";
		token.type = TRUE;
		token.line = tokens[current].line;
		condition = std::make_shared<Expression*>(new Literal(token));
	}

	body = std::make_shared<Statement*>(new WhileStatement(condition, body));
	if (initializer != nullptr) {
		body = std::make_shared<Statement*>(new Block({ initializer,body }));
	}
	return body;
}

lox::StmtPtr lox::Parser::function(std::string kind)
{
	Token name = consume(IDENTIFIER, "Expect " + kind + " name.");
	consume(LEFT_PAREN, "Expect \'(\' after " + kind + " name.");
	std::deque<Token> parameters;
	if (!check(RIGHT_PAREN)) {
		do {
			if (parameters.size() >= 255)
				error(peek(), "Cannot have more than 255 parameters.");
			parameters.push_back(consume(IDENTIFIER, "Expect parameter name."));
		} while (match({ COMMA }));
	}
	consume(RIGHT_PAREN, "Expect \')\' after parameters.");
	consume(LEFT_BRACE, "Expect \'{\' before " + kind + " body.");
	std::deque<StmtPtr> body = block();
	return std::make_shared<Statement*>(new Function(name,parameters,body));
}

lox::StmtPtr lox::Parser::ifStatement()
{
	consume(LEFT_PAREN, "Expect \'(\' after \'if\'.");
	ExprPtr condition = expression();
	consume(RIGHT_PAREN, "Expect \')\' after \'if\' condition.");
	StmtPtr thenBranch = statement();
	StmtPtr elseBranch = nullptr;
	if (match({ ELSE })) {
		elseBranch = statement();
	}
	return std::make_shared<Statement*>(new IfStatement(condition, thenBranch, elseBranch));
}

lox::StmtPtr lox::Parser::printStatement()
{
	ExprPtr value = expression();
	consume(SEMICOLON, "Expect \';\' after value.");
	return std::make_shared<Statement*>(new Print(value));
}

lox::StmtPtr lox::Parser::whileStatement()
{
	consume(LEFT_PAREN, "Expect \'(\' after \'while\'.");
	ExprPtr condition = expression();
	consume(RIGHT_PAREN, "Expect \')\' after \'while\' condition.");
	StmtPtr body = statement();
	return std::make_shared<Statement*>(new WhileStatement(condition, body));
}

lox::StmtPtr lox::Parser::expressionStatement()
{
	ExprPtr expr = expression();
	consume(SEMICOLON, "Expect \';\' after expression");
	return std::make_shared<Statement*>(new ExpressionStatement(expr));
}

std::deque<lox::StmtPtr> lox::Parser::block()
{
	std::deque<StmtPtr> statements;
	while (!check(RIGHT_BRACE) && !isAtEnd()) {
		statements.push_back(declaration());
	}
	consume(RIGHT_BRACE, "Expect \'}\' after block.");
	return statements;
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
