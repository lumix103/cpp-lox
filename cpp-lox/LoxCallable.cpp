#include "LoxCallable.h"
#include <chrono>
#include "Environment.h"
int lox::ClockCallable::arity()
{
	return 0;
}

std::shared_ptr<lox::Value> lox::ClockCallable::call(Interpreter* interpreter, std::deque<std::shared_ptr<Value>> args)
{
	Value return_value;
	return_value.vtype = DOUBLE;
	return_value.value = static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count()) / 1000.0;
	return std::make_shared<Value>(return_value);
}

std::string lox::ClockCallable::toString()
{
	return "<native fn>";
}

lox::LoxFunction::LoxFunction(std::shared_ptr<Function*> declaration)
{
	this->declaration = declaration;
}

int lox::LoxFunction::arity()
{
	return (*declaration)->params.size();
}

std::shared_ptr<lox::Value> lox::LoxFunction::call(Interpreter* interpreter, std::deque<std::shared_ptr<Value>> args)
{
	std::shared_ptr<Environment*> env = std::make_shared<Environment*>(new Environment(interpreter->globals));
	for (int i = 0; i < (*declaration)->params.size(); i++) {
		(*env)->define((*declaration)->params[i].lexeme, args[i]);
	}
	interpreter->executeBlock((*declaration)->body, env);
	std::shared_ptr<Value> null = std::make_shared<Value>();
	null->vtype = VType::NIL_PTR;
	null->value = nullptr;
	return null;
}

std::string lox::LoxFunction::toString()
{
	return "<fn " + (*declaration)->name.lexeme + ">";
}
