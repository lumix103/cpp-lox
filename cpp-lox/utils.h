#ifndef UTILS_H
#define UTILS_H

#include "Token.h"

namespace lox {
	void error(int line, const char* message);
	void error(Token token, const char* message);
	void report(int line, const char* where, const char* message);
	static bool hadError = false;
}
#endif // !UTILS_H
