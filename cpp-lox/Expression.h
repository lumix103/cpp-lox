#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "Token.h"
#include <memory>
#include <deque>

namespace lox {
	struct Expression {
		virtual ~Expression() {}
		virtual std::shared_ptr<void> accept(class Visitor* visitor) = 0;
	};

	std::shared_ptr<Expression*> typedef ExprPtr;

	struct Assign : Expression {
		Token name;
		ExprPtr value;

		Assign(Token name, ExprPtr value) : name(name) {
			this->value = std::move(value);
		}
		std::shared_ptr<void> accept(Visitor* visitor);
	};

	struct Binary : Expression {
		ExprPtr left;
		Token op;
		ExprPtr right;

		Binary(ExprPtr left, Token op, ExprPtr right) : op(op) {
			this->left = std::move(left);
			this->right = std::move(right);
		}

		std::shared_ptr<void> accept(Visitor* visitor);
	};

	struct Call : Expression {
		ExprPtr calle;
		Token paren;
		std::deque<ExprPtr> arguments;

		//If your stumbling back here its because the deque of unique pointers being copied and past self
		//said "I told you so"
		Call(ExprPtr calle, Token paren, std::deque<ExprPtr> arguments) : paren(paren) {
			this->calle = std::move(calle);
			this->arguments = std::move(arguments);
		}

		std::shared_ptr<void> accept(Visitor* visitor);
	};

	struct Get : Expression {
		ExprPtr object;
		Token name;

		Get(ExprPtr object, Token name) : name(name) {
			this->object = std::move(object);
		}

		std::shared_ptr<void> accept(Visitor* visitor);
	};

	struct Grouping : Expression {
		ExprPtr expression;

		Grouping(ExprPtr expression) {
			this->expression = std::move(expression);
		}

		std::shared_ptr<void> accept(Visitor* visitor);
	};

	struct Literal : Expression {
		Token value;

		Literal(Token value) : value(value) {}

		std::shared_ptr<void> accept(Visitor* visitor);
	};

	struct Logical : Expression {
		ExprPtr left;
		Token op;
		ExprPtr right;

		Logical(ExprPtr left, Token op, ExprPtr right) : op(op) {
			this->left = std::move(left);
			this->right = std::move(right);
		}

		std::shared_ptr<void> accept(Visitor* visitor);
	};

	struct Set : Expression {
		ExprPtr object;
		Token name;
		ExprPtr value;

		Set(ExprPtr object, Token name, ExprPtr value) : name(name) {
			this->object = std::move(object);
			this->value = std::move(value);
		}

		std::shared_ptr<void> accept(Visitor* visitor);
	};

	struct Super : Expression {
		Token keyword;
		Token method;

		Super(Token keyword, Token method) : keyword(keyword), method(method) {}

		std::shared_ptr<void> accept(Visitor* visitor);

	};

	struct This : Expression {
		Token keyword;

		This(Token keyword) : keyword(keyword) {}

		std::shared_ptr<void> accept(Visitor* visitor);
	};

	struct Unary : Expression {
		Token op;
		ExprPtr right;

		Unary(Token op, ExprPtr right) : op(op) {
			this->right = std::move(right);
		}

		std::shared_ptr<void> accept(Visitor* visitor);
	};

	struct Variable : Expression {
		Token name;

		Variable(Token name) : name(name) {}

		std::shared_ptr<void> accept(Visitor* visitor);
	};

	class Visitor {
	public:
		virtual std::shared_ptr<void> visit(Assign* _assign) = 0;
		virtual std::shared_ptr<void> visit(Binary* _binary) = 0;
		virtual std::shared_ptr<void> visit(Call* _call) = 0;
		virtual std::shared_ptr<void> visit(Get* _get) = 0;
		virtual std::shared_ptr<void> visit(Grouping* _grouping) = 0;
		virtual std::shared_ptr<void> visit(Literal* _literal) = 0;
		virtual std::shared_ptr<void> visit(Logical* _logical) = 0;
		virtual std::shared_ptr<void> visit(Set* _set) = 0;
		virtual std::shared_ptr<void> visit(Super* _super) = 0;
		virtual std::shared_ptr<void> visit(This* _this) = 0;
		virtual std::shared_ptr<void> visit(Unary* _unary) = 0;
		virtual std::shared_ptr<void> visit(Variable* _variable) = 0;
	};
}

#endif //EXPRESSION_H