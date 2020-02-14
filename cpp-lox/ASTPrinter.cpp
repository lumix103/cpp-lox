#include "ASTPrinter.h"

std::string lox::ASTPrinter::parenthesize(std::string name, std::list<Expression*> expressions)
{
	std::string str = "";
	str.push_back('(');
	str.append(name);
	for (auto expr : expressions) {
		str.push_back(' ');
		str.append(expr->accept(this));
	}
	str.push_back(')');
	return str;
}

std::string lox::ASTPrinter::print(Expression* expression)
{
	return expression->accept(this);
}

std::string lox::ASTPrinter::visit(Binary* _binary)
{
	return parenthesize(_binary->op.lexeme, { *_binary->left, *_binary->right });
}

std::string lox::ASTPrinter::visit(Grouping* _grouping)
{
	return parenthesize("group", { *_grouping->expression });
}

std::string lox::ASTPrinter::visit(Literal* _literal)
{
	return _literal->value.lexeme;
}

std::string lox::ASTPrinter::visit(Unary* _unary)
{
	return parenthesize(_unary->op.lexeme, { *_unary->right });
}
