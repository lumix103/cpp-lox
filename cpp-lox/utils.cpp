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

lox::ExprStmtType lox::IsA::operator()(Expression* _expression)
{
	std::shared_ptr<ExprStmtType> type = std::static_pointer_cast<ExprStmtType>(_expression->accept(this));
	return *type;
}

std::shared_ptr<void> lox::IsA::visit(Binary* _binary)
{
	return std::make_shared<ExprStmtType>(EXPR_BINARY);
}

std::shared_ptr<void> lox::IsA::visit(Grouping* _grouping)
{
	return std::make_shared<ExprStmtType>(EXPR_GROUPING);
}

std::shared_ptr<void> lox::IsA::visit(Literal* _literal)
{
	return std::make_shared<ExprStmtType>(EXPR_LITERAL);
}

std::shared_ptr<void> lox::IsA::visit(Unary* _unary)
{
	return std::make_shared<ExprStmtType>(EXPR_UNARY);
}

std::shared_ptr<void> lox::IsA::visit(Assign* _assign)
{
	return std::make_shared<ExprStmtType>(EXPR_ASSIGN);
}

std::shared_ptr<void> lox::IsA::visit(Call* _call)
{
	return std::make_shared<ExprStmtType>(EXPR_CALL);
}

std::shared_ptr<void> lox::IsA::visit(Get* _get)
{
	return std::make_shared<ExprStmtType>(EXPR_GET);
}

std::shared_ptr<void> lox::IsA::visit(Logical* _logical)
{
	return std::make_shared<ExprStmtType>(EXPR_LOGICAL);
}

std::shared_ptr<void> lox::IsA::visit(Set* _set)
{
	return std::make_shared<ExprStmtType>(EXPR_SET);
}

std::shared_ptr<void> lox::IsA::visit(Super* _super)
{
	return std::make_shared<ExprStmtType>(EXPR_SUPER);
}

std::shared_ptr<void> lox::IsA::visit(This* _this)
{
	return std::make_shared<ExprStmtType>(EXPR_THIS);
}

std::shared_ptr<void> lox::IsA::visit(Variable* _variable)
{
	return std::make_shared<ExprStmtType>(EXPR_VARIABLE);
}
