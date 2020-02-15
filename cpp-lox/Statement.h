#ifndef STATEMENT_H
#define STATEMENT_H

#include "Token.h"
#include "Expression.h"
#include <memory>
#include <deque>

namespace lox {
	struct Statement {
		virtual ~Statement() {}
		virtual std::shared_ptr<void> accept(class StatementVisitor* visitor) = 0;
	};

	std::shared_ptr<Statement*> typedef StmtPtr;

	struct Block : public Statement {
		std::deque<StmtPtr> statements;

		Block(std::deque<StmtPtr> statements) : statements(statements) {}

		std::shared_ptr<void> accept(StatementVisitor* visitor);
	};

	struct Class : public Statement {
		Token name;
		std::shared_ptr<Variable*> superclass;
		std::deque<std::shared_ptr<struct Function*>> methods;
		Class(Token name, std::shared_ptr<Variable*> superclass, std::deque<std::shared_ptr<Function*>> methods) : name(name), superclass(superclass), methods(methods) {}

		std::shared_ptr<void> accept(StatementVisitor* visitor);
	};

	struct ExpressionStatement : public Statement {
		ExprPtr expression;
		ExpressionStatement(ExprPtr expression) : expression(expression) {}
		std::shared_ptr<void> accept(StatementVisitor* visitor);
	};

	struct Function : public Statement {
		Token name;
		std::deque<Token> params;
		std::deque<StmtPtr> body;
		Function(Token name, std::deque<Token> params, std::deque<StmtPtr> body) : name(name), params(params), body(body) {}

		std::shared_ptr<void> accept(StatementVisitor* visitor);
	};

	struct IfStatement : public Statement {
		ExprPtr condition;
		StmtPtr thenBranch;
		StmtPtr elseBranch;
		IfStatement(ExprPtr condition, StmtPtr thenBranch, StmtPtr elseBranch) : condition(condition), thenBranch(thenBranch), elseBranch(elseBranch){}
		
		std::shared_ptr<void> accept(StatementVisitor* visitor);
	};

	struct Print : public Statement {
		ExprPtr expression;

		Print(ExprPtr expression) : expression(expression) {}

		std::shared_ptr<void> accept(StatementVisitor* visitor);
	};

	struct ReturnStatement : public Statement {
		Token keyword;
		ExprPtr value;
		ReturnStatement(Token keyword, ExprPtr value) : keyword(keyword), value(value) {}
		
		std::shared_ptr<void> accept(StatementVisitor* visitor);
	};

	struct Var : public Statement {
		Token name;
		ExprPtr initializer;
		Var(Token name, ExprPtr initializer) : name(name), initializer(initializer) {}

		std::shared_ptr<void> accept(StatementVisitor* visitor);
	};

	struct WhileStatement : public Statement {
		ExprPtr condition;
		StmtPtr body;
		WhileStatement(ExprPtr condition, StmtPtr body) : condition(condition), body(body) {}

		std::shared_ptr<void> accept(StatementVisitor* visitor);

	};

	class StatementVisitor {
	public:
		virtual std::shared_ptr<void> visit(Block* _block) = 0;
		virtual std::shared_ptr<void> visit(Class* _class) = 0;
		virtual std::shared_ptr<void> visit(ExpressionStatement* _expression) = 0;
		virtual std::shared_ptr<void> visit(Function* _function) = 0;
		virtual std::shared_ptr<void> visit(IfStatement* _if) = 0;
		virtual std::shared_ptr<void> visit(Print* _print) = 0;
		virtual std::shared_ptr<void> visit(ReturnStatement* _return) = 0;
		virtual std::shared_ptr<void> visit(Var* _var) = 0;
		virtual std::shared_ptr<void> visit(WhileStatement* _while) = 0;
	};
}

#endif //STATEMENT_H