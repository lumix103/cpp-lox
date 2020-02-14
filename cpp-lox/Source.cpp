#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include "Lexer.h"
#include "utils.h"
#include "ASTPrinter.h"
#include "Parser.h"
void runFile(const char* file_path);
void runPrompt();

void run(std::string input);

void start(int argc, char** argv);

int main(int argc, char** argv) {
	/*
	lox::Token unary_op = {lox::MINUS, "-" ,1 , ""};
	lox::Token literal_value = { lox::NUMBER, "123", 1, "123" };
	auto literal_expr = std::make_unique<lox::Expression*>(new lox::Literal(literal_value));
	auto unary_expr = std::make_unique<lox::Expression*>(new lox::Unary(unary_op, std::move(literal_expr)));

	literal_value.lexeme = "45.67";
	literal_value.value = "45.67";
	auto literal_expr1 = std::make_unique<lox::Expression*>(new lox::Literal(literal_value));
	auto grouping = std::make_unique<lox::Expression*>(new lox::Grouping(std::move(literal_expr1)));

	lox::Token binary_op = { lox::STAR, "*", 1, "" };

	auto binary = std::make_unique<lox::Expression*>(new lox::Binary(std::move(unary_expr), binary_op, std::move(grouping)));

	lox::ASTPrinter printer;

	std::cout << printer.print(*binary) << std::endl;
	*/
	start(argc, argv);
	return 0;
}

void runFile(const char* file_path) {
	std::fstream file;
	file.open(file_path, std::ios::in);
	if (!file.is_open()) {
		std::cout << "File not found: " << file_path << "\n";
		exit(65);
	}
	std::string input, line;
	while (std::getline(file, input))
		input += line;
	file.close();
	run(input);
	if (lox::hadError) exit(65);

}

void runPrompt() {
	std::string input;
	int line = 0;
	for (;;) {
		std::cout << line + 1 << "> ";
		std::getline(std::cin, input);
		if (std::cin.fail() || std::cin.eof()) {
			std::cin.clear();
			std::exit(EXIT_SUCCESS);
		}
		run(input);
		lox::hadError = false;
		line++;
	}
}

void run(std::string input) {
	lox::Lexer lexer(input);
	auto tokens = lexer.scanTokens();
	lox::Parser parser(tokens);
	lox::ExprPtr expr = std::move(parser.parse());
	if (lox::hadError) return;
	lox::ASTPrinter printer;
	std::cout << printer.print(*expr) << std::endl;
}

void start(int argc, char** argv) {
	if (argc > 2) {
		std::cout << "Usage: cppLox [script]\n";
		exit(64);
	}
	else if (argc == 2) {
		runFile(argv[1]); //First arguement should be file dir
	}
	else {
		runPrompt();
	}
}