#include "Expression.h"

namespace lox {

	std::shared_ptr<void> Assign::accept(ExpressionVisitor* visitor) {
		return visitor->visit(this);
	}

	std::shared_ptr<void> Binary::accept(ExpressionVisitor* visitor) {
		return visitor->visit(this);
	}

	std::shared_ptr<void> Call::accept(ExpressionVisitor* visitor) {
		return visitor->visit(this);
	}
	std::shared_ptr<void> Get::accept(ExpressionVisitor* visitor) {
		return visitor->visit(this);
	}

	std::shared_ptr<void> Grouping::accept(ExpressionVisitor* visitor) {
		return visitor->visit(this);
	}

	std::shared_ptr<void> Literal::accept(ExpressionVisitor* visitor) {
		return visitor->visit(this);
	}

	std::shared_ptr<void> Logical::accept(ExpressionVisitor* visitor) {
		return visitor->visit(this);
	}

	std::shared_ptr<void> Set::accept(ExpressionVisitor* visitor) {
		return visitor->visit(this);
	}
	std::shared_ptr<void> Super::accept(ExpressionVisitor* visitor) {
		return visitor->visit(this);
	}
	std::shared_ptr<void> This::accept(ExpressionVisitor* visitor) {
		return visitor->visit(this);
	}
	std::shared_ptr<void> Unary::accept(ExpressionVisitor* visitor) {
		return visitor->visit(this);
	}
	std::shared_ptr<void> Variable::accept(ExpressionVisitor* visitor) {
		return visitor->visit(this);
	}
}