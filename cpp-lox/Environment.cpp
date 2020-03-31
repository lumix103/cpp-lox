#include "Environment.h"

lox::Environment::Environment()
{
	enclosing = nullptr;
	NIL = std::make_shared<Value>();
	NIL->vtype = NIL_PTR;
	NIL->value = nullptr;
}

lox::Environment::Environment(std::shared_ptr<Environment*> enclosing)
{
	this->enclosing = enclosing;
}

void lox::Environment::define(std::string name, std::shared_ptr<Value> value)
{
	values.insert({ name, std::move(value) });
}

const std::shared_ptr<lox::Value> lox::Environment::get(lox::Token name)
{
	auto key = values.find(name.lexeme);
	if (key != values.cend()) {
		return key->second;
	}

	if (enclosing != nullptr) return (*enclosing)->get(name);

	throw RuntimeError(name, "Undefined variable \'" + name.lexeme + ".");
	return NIL;
}

void lox::Environment::assign(Token name, std::shared_ptr<Value> value)
{
	auto key = values.find(name.lexeme);
	if (key != values.cend()) {
		values.erase(key);
		values.insert({ name.lexeme, std::move(value) });
		return;
	}
	if (enclosing != nullptr) {
		(*enclosing)->assign(name, std::move(value));
		return;
	}
	throw RuntimeError(name, "Undefined variable \'" + name.lexeme + "\'.");
}
