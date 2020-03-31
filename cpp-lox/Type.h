#ifndef TYPE_H
#define TYPE_H

#include <memory>
#include <variant>
#include <string>

namespace lox {
	class LoxCallable;
	enum VType {
		DOUBLE,
		BOOL,
		STR,
		NIL_PTR,
		CALLABLE
	};
	
	struct Value {
		VType vtype;
		std::variant<double, bool, std::string, std::shared_ptr<LoxCallable*>,void*> value;
	};

}

#endif // !TYPE_H
