#ifndef ASTPRINTER_H
#define ASTPRINTER_H

#include "Expression.h"

namespace lox {
	class ASTPrinter : public Visitor {
	private:
		std::string parenthesize(std::string name, std::list<Expression*> expressions);
	public:
		std::string print(Expression* expression);
		std::string visit(Binary* _binary);
		std::string visit(Grouping* _grouping);
		std::string visit(Literal* _literal);
		std::string visit(Unary* _unary);

		virtual std::string visit(Assign* _assign) { return "Unimplemented"; };
		virtual std::string visit(Call* _call) { return "Unimplemented"; };
		virtual std::string visit(Get* _get) { return "Unimplemented"; };
		virtual std::string visit(Logical* _logical) { return "Unimplemented"; };
		virtual std::string visit(Set* _set) { return "Unimplemented"; };
		virtual std::string visit(Super* _super) { return "Unimplemented"; };
		virtual std::string visit(This* _this) { return "Unimplemented"; };
		virtual std::string visit(Variable* _variable) { return "Unimplemented"; };
	};
}

#endif //ASTPRINTER_H