#ifndef UTILS_H
#define UTILS_H

#include "Token.h"
#include "Interpreter.h"
#include "Expression.h"
namespace lox {
	class ParseError : public std::exception {};
	class RuntimeError : public std::exception {
	public:
		Token op;
		std::string messgae;
	public:
		RuntimeError(Token op, std::string message);
		const char* what() const throw();
	};

	enum ExprStmtType {
		EXPR_BINARY,
		EXPR_GROUPING,
		EXPR_LITERAL,
		EXPR_UNARY,
		EXPR_ASSIGN,
		EXPR_CALL,
		EXPR_GET,
		EXPR_LOGICAL,
		EXPR_SET,
		EXPR_SUPER,
		EXPR_THIS,
		EXPR_VARIABLE
	};

	class IsA : public ExpressionVisitor {
	public:
		ExprStmtType operator()(Expression* _expression);
		std::shared_ptr<void> visit(Assign* _assign);
		std::shared_ptr<void> visit(Binary* _binary);
		std::shared_ptr<void> visit(Grouping* _grouping);
		std::shared_ptr<void> visit(Literal* _literal);
		std::shared_ptr<void> visit(Unary* _unary);
		std::shared_ptr<void> visit(Call* _call);
		std::shared_ptr<void> visit(Get* _get);
		std::shared_ptr<void> visit(Logical* _logical);
		std::shared_ptr<void> visit(Set* _set);
		std::shared_ptr<void> visit(Super* _super);
		std::shared_ptr<void> visit(This* _this);
		std::shared_ptr<void> visit(Variable* _variable);
	};

	void error(int line, const char* message);
	void error(Token token, const char* message);
	void report(int line, const char* where, const char* message);
	void runtimeError(RuntimeError error);
	static bool hadError = false;
	static bool hadRuntimeError = false;
}
#endif // !UTILS_H
