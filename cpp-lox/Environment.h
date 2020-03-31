#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <memory>
#include <unordered_map>
#include <string>
#include "Type.h"
#include "Token.h"
#include "utils.h"
namespace lox {
	class Environment {
	public:
		Environment();
		Environment(std::shared_ptr<Environment*> enclosing);
		void define(std::string name, std::shared_ptr<Value> value);
		const std::shared_ptr<Value> get(Token name);
		void assign(Token name, std::shared_ptr<Value> value);
	private:
		std::unordered_map<std::string, std::shared_ptr<Value>> values;
		std::shared_ptr<Environment*> enclosing;
		std::shared_ptr<Value> NIL;
	};
}

#endif // !ENVIRONMENT_H
