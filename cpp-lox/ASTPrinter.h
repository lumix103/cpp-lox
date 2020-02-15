#ifndef ASTPRINTER_H
#define ASTPRINTER_H

#include "Expression.h"

namespace lox {
	class ASTPrinter : public ExpressionVisitor {
	private:
		std::string parenthesize(std::string name, std::list<Expression*> expressions);
	public:
		std::string print(Expression* expression);
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

#endif //ASTPRINTER_H