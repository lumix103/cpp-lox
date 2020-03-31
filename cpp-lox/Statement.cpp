#include "Statement.h"

void lox::Block::accept(StatementVisitor* visitor)
{
	visitor->visit(this);
}

void lox::Class::accept(StatementVisitor* visitor)
{
	visitor->visit(this);
}

void lox::ExpressionStatement::accept(StatementVisitor* visitor)
{
	visitor->visit(this);
}

void lox::Function::accept(StatementVisitor* visitor)
{
	visitor->visit(this);
}

void lox::IfStatement::accept(StatementVisitor* visitor)
{
	visitor->visit(this);
}

void lox::Print::accept(StatementVisitor* visitor)
{
	visitor->visit(this);
}

void lox::ReturnStatement::accept(StatementVisitor* visitor)
{
	visitor->visit(this);
}

void lox::Var::accept(StatementVisitor* visitor)
{
	visitor->visit(this);
}

void lox::WhileStatement::accept(StatementVisitor* visitor)
{
	visitor->visit(this);
}
