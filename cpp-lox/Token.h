#pragma once
#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <any>
#include <unordered_map>

namespace lox {
	enum TokenType {
		// Single-character tokens.                      
		LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
		COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

		// One or two character tokens.                  
		BANG, BANG_EQUAL,
		EQUAL, EQUAL_EQUAL,
		GREATER, GREATER_EQUAL,
		LESS, LESS_EQUAL,

		// Literals.                                     
		IDENTIFIER, STRING, NUMBER,

		// Keywords.                                     
		AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
		PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,

		END_OF_FILE
	};

	struct Token {
		TokenType type;
		std::string lexeme;
		int line;
		std::string value;
	};
	void pretty_print_token(const Token token);
	static std::unordered_map<std::string, TokenType> keywords({
			{"and",		AND},
			{"class",	CLASS},
			{"else",	ELSE},
			{"false",	FALSE},
			{"for",		FOR},
			{"fun",		FUN},
			{"if",		IF},
			{"nil",		NIL},
			{"or",		OR},
			{"print",	PRINT},
			{"return",	RETURN},
			{"super",	SUPER},
			{"this",	THIS},
			{"true",	TRUE},
			{"var",		VAR},
			{"while",	WHILE}
		});
}
#endif // !TOKEN_H
