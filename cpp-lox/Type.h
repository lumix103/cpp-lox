#ifndef TYPE_H
#define TYPE_H

#include <variant>
#include <string>

namespace lox {
	
	enum VType {
		DOUBLE,
		BOOL,
		STR,
		NIL_PTR
	};
	
	struct Value {
		VType vtype;
		std::variant<double, bool, std::string> value;
	};

}

#endif // !TYPE_H
