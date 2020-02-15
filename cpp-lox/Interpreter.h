#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "Expression.h"
#include "Type.h"
#include "utils.h"
#include "Statement.h"
namespace lox {
	
	class Interpreter : public ExpressionVisitor, public StatementVisitor {
	private:
		bool isTruthy(std::shared_ptr<Value> value);
		bool isEqual(std::shared_ptr<Value> left, std::shared_ptr<Value> right);
		void checkNumberOperand(Token op, std::shared_ptr<Value> operand);
		void checkNumberOperands(Token op, std::shared_ptr<Value> left, std::shared_ptr<Value> right);
		std::shared_ptr<Value> evaluate(Expression* expression);
		void executeBlock(std::deque<StmtPtr> statements, std::shared_ptr<class Environment*> env);
		static std::shared_ptr<Interpreter*> instance;
		std::shared_ptr<Environment*> env;
		Interpreter();
	public:
		static std::shared_ptr<Interpreter*> getInstance();
		//void interpret(Expression* expression);
		void interpret(std::deque<StmtPtr> statements);
		void execute(StmtPtr statement);

		std::shared_ptr<void> visit(Binary* _binary);
		std::shared_ptr<void> visit(Grouping* _grouping);
		std::shared_ptr<void> visit(Literal* _literal);
		std::shared_ptr<void> visit(Unary* _unary);

		std::shared_ptr<void> visit(Assign* _assign);
		virtual std::shared_ptr<void> visit(Call* _call) { return nullptr; };
		virtual std::shared_ptr<void> visit(Get* _get) { return nullptr; };
		virtual std::shared_ptr<void> visit(Logical* _logical) { return nullptr; };
		virtual std::shared_ptr<void> visit(Set* _set) { return nullptr; };
		virtual std::shared_ptr<void> visit(Super* _super) { return nullptr; };
		virtual std::shared_ptr<void> visit(This* _this) { return nullptr; };
		virtual std::shared_ptr<void> visit(Variable* _variable);

		std::shared_ptr<void> visit(ExpressionStatement* _expression);
		std::shared_ptr<void> visit(Print* _print);

		std::shared_ptr<void> visit(Block* _block);
		virtual std::shared_ptr<void> visit(Class* _class) { return nullptr; }
		virtual std::shared_ptr<void> visit(Function* _function) { return nullptr; }
		virtual std::shared_ptr<void> visit(IfStatement* _if) { return nullptr; }
		virtual std::shared_ptr<void> visit(ReturnStatement* _return) { return nullptr; }
		virtual std::shared_ptr<void> visit(Var* _var);
		virtual std::shared_ptr<void> visit(WhileStatement* _while) { return nullptr; }
	};

}

#endif //INTERPRETER_H