#include "Expression.h"

namespace lox {

	std::shared_ptr<void> Assign::accept(Visitor* visitor) {
		return visitor->visit(this);
	}

	std::shared_ptr<void> Binary::accept(Visitor* visitor) {
		return visitor->visit(this);
	}

	std::shared_ptr<void> Call::accept(Visitor* visitor) {
		return visitor->visit(this);
	}
	std::shared_ptr<void> Get::accept(Visitor* visitor) {
		return visitor->visit(this);
	}

	std::shared_ptr<void> Grouping::accept(Visitor* visitor) {
		return visitor->visit(this);
	}

	std::shared_ptr<void> Literal::accept(Visitor* visitor) {
		return visitor->visit(this);
	}

	std::shared_ptr<void> Logical::accept(Visitor* visitor) {
		return visitor->visit(this);
	}

	std::shared_ptr<void> Set::accept(Visitor* visitor) {
		return visitor->visit(this);
	}
	std::shared_ptr<void> Super::accept(Visitor* visitor) {
		return visitor->visit(this);
	}
	std::shared_ptr<void> This::accept(Visitor* visitor) {
		return visitor->visit(this);
	}
	std::shared_ptr<void> Unary::accept(Visitor* visitor) {
		return visitor->visit(this);
	}
	std::shared_ptr<void> Variable::accept(Visitor* visitor) {
		return visitor->visit(this);
	}
}