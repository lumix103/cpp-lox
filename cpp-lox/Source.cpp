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
	if (lox::hadRuntimeError) exit(70);

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
	std::deque<lox::StmtPtr> statements = parser.parse();
	if (lox::hadError) return;
	lox::Interpreter* interpreter = *lox::Interpreter::getInstance();
	interpreter->interpret(statements);
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