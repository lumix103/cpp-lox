#ifndef LOXCALLABLE_H
#define LOXCALLABLE_H

#include "Type.h"
#include "Interpreter.h"
namespace lox {
	class LoxCallable {
	public:
		virtual int arity() = 0;
		virtual std::shared_ptr<Value> call(Interpreter* interpreter, std::deque<std::shared_ptr<Value>> args) = 0;
		virtual std::string toString() = 0;
	};

	class LoxFunction : public LoxCallable {
	private:
		std::shared_ptr<Function*> declaration;
	public:
		LoxFunction(std::shared_ptr<Function*> declaration);
		int arity();
		std::shared_ptr<Value> call(Interpreter* interpreter, std::deque<std::shared_ptr<Value>> args);
		std::string toString();
	};

	class ClockCallable : public LoxCallable {
	public:
		int arity();
		std::shared_ptr<Value> call(Interpreter* interpreter, std::deque<std::shared_ptr<Value>> args);
		std::string toString();
	};
}

#endif //LOXCALLABLE_H