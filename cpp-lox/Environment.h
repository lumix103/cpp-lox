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
		void define(std::string name, Value value);
		Value get(Token name);
		void assign(Token name, Value value);
	private:
		std::unordered_map<std::string, Value> values;
		std::shared_ptr<Environment*> enclosing;
	};
}

#endif // !ENVIRONMENT_H
