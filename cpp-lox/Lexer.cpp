#include "Lexer.h"
#include "utils.h"
#include <iostream>
lox::Lexer::Lexer(std::string input)
{
	this->input = input;
	line = 1;
}

std::deque<lox::Token> lox::Lexer::scanTokens()
{
	while (!isAtEnd()) {
		start = current;
		scanToken();
	}
	tokens.push_back(Token({ TokenType::END_OF_FILE,
						"",line }));
	return tokens;
}

void lox::Lexer::scanToken()
{
	char c = advance();
	switch (c) {
	case '(': addToken(LEFT_PAREN); break;
	case ')': addToken(RIGHT_PAREN); break;
	case '{': addToken(LEFT_BRACE); break;
	case '}': addToken(RIGHT_BRACE); break;
	case ',': addToken(COMMA); break;
	case '.': addToken(DOT); break;
	case '-': addToken(MINUS); break;
	case '+': addToken(PLUS); break;
	case ';': addToken(SEMICOLON); break;
	case '*': addToken(STAR); break;
	case '!': addToken(match('=') ? BANG_EQUAL : BANG); break;
	case '=': addToken(match('=') ? EQUAL_EQUAL : EQUAL); break;
	case '<': addToken(match('=') ? LESS_EQUAL : LESS); break;
	case '>': addToken(match('=') ? GREATER_EQUAL : GREATER); break;
	case '/':
		if (match('/')) {
			// A comment goes until the end of the line.
			while (peek() != '\n' && !isAtEnd()) advance();
		}
		else if (match('*')) {
			comment();
		}
		else {
			addToken(SLASH);
		}
		break;
	case ' ':
	case '\r':
	case '\t':
		// Ignore whitespace.                      
		break;
	case '\n':
		line++;

		break;
	case '"': string(); break;
	default:
		if (std::isdigit(c)) {
			number();
		}
		else if (std::isalnum(c)) {
			identifier();
		}
		else {
			lox::error(line, "Unexpected character.");
		}
		break;
	}

}

bool lox::Lexer::isAtEnd()
{
	return current >= input.length();
}

bool lox::Lexer::match(char c)
{
	if (isAtEnd()) return false;
	if (input[current] != c) return false;

	current++;
	return true;
}

char lox::Lexer::advance()
{
	current++;
	return input[current - 1];
}

char lox::Lexer::peek()
{
	if (isAtEnd()) return '\0';
	return input[current];
}

char lox::Lexer::peekNext()
{
	if (current + 1 >= input.length()) return '\0';
	return input[current + 1];
}

void lox::Lexer::addToken(TokenType type)
{
	addToken(type, "");
}

void lox::Lexer::addToken(TokenType type, std::string literal)
{
	std::string text = input.substr(start, current - start);
	if (literal.length() != 0) {
		tokens.push_back(Token({ type,text,line,literal }));
		return;
	}
	tokens.push_back(Token({ type,text,line }));
}

void lox::Lexer::string()
{
	while (peek() != '"' && !isAtEnd()) {
		if (peek() == '\n') line++;
		advance();
	}

	// Unterminated string.                                 
	if (isAtEnd()) {
		lox::error(line, "Unterminated string.");
		return;
	}

	// The closing ".                                       
	advance();

	// Trim the surrounding quotes.                         
	std::string value = input.substr(start + 1, current - start - 2);
	//std::cout << value << std::endl;
	addToken(STRING, value);
}

void lox::Lexer::number()
{
	while (std::isdigit(peek())) advance();

	// Look for a fractional part.                            
	if (peek() == '.' && isdigit(peekNext())) {
		// Consume the "."                                      
		advance();

		while (isdigit(peek())) advance();
	}

	addToken(NUMBER, input.substr(start, current - start));
}

void lox::Lexer::identifier()
{
	while (std::isalnum(peek()) || peek() == '_') advance();

	std::string text = input.substr(start, current - start);
	TokenType type = IDENTIFIER;
	auto key = lox::keywords.find(text);
	if (key != lox::keywords.cend()) {
		type = key->second;
	}
	addToken(type);
}

void lox::Lexer::comment()
{
	char c = input[current];
	while (!isAtEnd())
	{
		if (c == 'n') line++;
		if (c == '*')
		{
			if (match('/'))
			{
				return;
			}
		}
		c = advance();
	}

}
