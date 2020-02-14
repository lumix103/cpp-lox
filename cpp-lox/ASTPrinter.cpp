#include "ASTPrinter.h"

std::string lox::ASTPrinter::parenthesize(std::string name, std::list<Expression*> expressions)
{
	std::string str = "";
	str.push_back('(');
	str.append(name);
	for (auto expr : expressions) {
		str.push_back(' ');
		std::shared_ptr<std::string> var = std::static_pointer_cast<std::string>(expr->accept(this));
		str.append(*var);
	}
	str.push_back(')');
	return str;
}

std::string lox::ASTPrinter::print(Expression* expression)
{
	return *(std::static_pointer_cast<std::string>(expression->accept(this)));
}

std::shared_ptr<void> lox::ASTPrinter::visit(Binary* _binary)
{
	return std::make_shared<std::string>(parenthesize(_binary->op.lexeme, { *_binary->left, *_binary->right }));
}

std::shared_ptr<void> lox::ASTPrinter::visit(Grouping* _grouping)
{
	return std::make_shared<std::string>(parenthesize("group", { *_grouping->expression }));
}

std::shared_ptr<void> lox::ASTPrinter::visit(Literal* _literal)
{
	return std::make_shared<std::string>(_literal->value.lexeme);
}

std::shared_ptr<void> lox::ASTPrinter::visit(Unary* _unary)
{
	return std::make_shared<std::string>(parenthesize(_unary->op.lexeme, { *_unary->right }));
}
