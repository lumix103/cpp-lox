#ifndef UTILS_H
#define UTILS_H

#include "Token.h"

namespace lox {
	class ParseError : public std::exception {};
	class RuntimeError : public std::exception {
	private:
		Token op;
		std::string messgae;
	public:
		RuntimeError(Token op, std::string message);
		const char* what() const throw();
	};
	void error(int line, const char* message);
	void error(Token token, const char* message);
	void report(int line, const char* where, const char* message);
	static bool hadError = false;
}
#endif // !UTILS_H
