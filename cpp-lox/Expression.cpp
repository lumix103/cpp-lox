#include "Expression.h"

namespace lox {

	std::string Assign::accept(Visitor* visitor) {
		return visitor->visit(this);
	}

	std::string Binary::accept(Visitor* visitor) {
		return visitor->visit(this);
	}

	std::string Call::accept(Visitor* visitor) {
		return visitor->visit(this);
	}
	std::string Get::accept(Visitor* visitor) {
		return visitor->visit(this);
	}

	std::string Grouping::accept(Visitor* visitor) {
		return visitor->visit(this);
	}

	std::string Literal::accept(Visitor* visitor) {
		return visitor->visit(this);
	}

	std::string Logical::accept(Visitor* visitor) {
		return visitor->visit(this);
	}

	std::string Set::accept(Visitor* visitor) {
		return visitor->visit(this);
	}
	std::string Super::accept(Visitor* visitor) {
		return visitor->visit(this);
	}
	std::string This::accept(Visitor* visitor) {
		return visitor->visit(this);
	}
	std::string Unary::accept(Visitor* visitor) {
		return visitor->visit(this);
	}
	std::string Variable::accept(Visitor* visitor) {
		return visitor->visit(this);
	}
}