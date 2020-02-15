#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "Expression.h"
#include "Type.h"
#include "utils.h"

namespace lox {

	class Interpreter : public Visitor {
	private:
		bool isTruthy(std::shared_ptr<Value> value);
		bool isEqual(std::shared_ptr<Value> left, std::shared_ptr<Value> right);
		void checkNumberOperand(Token op, std::shared_ptr<Value> operand);
		void checkNumberOperands(Token op, std::shared_ptr<Value> left, std::shared_ptr<Value> right);
		std::shared_ptr<Value> evaluate(Expression* expression);
		static std::shared_ptr<Interpreter*> instance;
	public:
		static std::shared_ptr<Interpreter*> getInstance();
		void interpret(Expression* expression);

		std::shared_ptr<void> visit(Binary* _binary);
		std::shared_ptr<void> visit(Grouping* _grouping);
		std::shared_ptr<void> visit(Literal* _literal);
		std::shared_ptr<void> visit(Unary* _unary);

		virtual std::shared_ptr<void> visit(Assign* _assign) { return nullptr; };
		virtual std::shared_ptr<void> visit(Call* _call) { return nullptr; };
		virtual std::shared_ptr<void> visit(Get* _get) { return nullptr; };
		virtual std::shared_ptr<void> visit(Logical* _logical) { return nullptr; };
		virtual std::shared_ptr<void> visit(Set* _set) { return nullptr; };
		virtual std::shared_ptr<void> visit(Super* _super) { return nullptr; };
		virtual std::shared_ptr<void> visit(This* _this) { return nullptr; };
		virtual std::shared_ptr<void> visit(Variable* _variable) { return nullptr; };

	};

}

#endif //INTERPRETER_H