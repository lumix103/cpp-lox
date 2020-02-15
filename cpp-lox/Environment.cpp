#include "Environment.h"

lox::Environment::Environment()
{
	enclosing = nullptr;
}

lox::Environment::Environment(std::shared_ptr<Environment*> enclosing)
{
	this->enclosing = enclosing;
}

void lox::Environment::define(std::string name, Value value)
{
	values.insert({ name,value });
}

lox::Value lox::Environment::get(lox::Token name)
{
	auto key = values.find(name.lexeme);
	if (key != values.cend()) {
		return key->second;
	}

	if (enclosing != nullptr) return (*enclosing)->get(name);

	throw RuntimeError(name, "Undefined variable \'" + name.lexeme + ".");
	Value value;
	value.vtype = NIL_PTR;
	value.value = nullptr;
	return value;
}

void lox::Environment::assign(Token name, Value value)
{
	auto key = values.find(name.lexeme);
	if (key != values.cend()) {
		values.erase(key);
		values.insert({ name.lexeme, value });
		return;
	}
	if (enclosing != nullptr) {
		(*enclosing)->assign(name, value);
		return;
	}
	throw RuntimeError(name, "Undefined variable \'" + name.lexeme + "\'.");
}
