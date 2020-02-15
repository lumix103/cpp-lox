#include "Statement.h"

std::shared_ptr<void> lox::Block::accept(StatementVisitor* visitor)
{
	return visitor->visit(this);
}

std::shared_ptr<void> lox::Class::accept(StatementVisitor* visitor)
{
	return visitor->visit(this);
}

std::shared_ptr<void> lox::ExpressionStatement::accept(StatementVisitor* visitor)
{
	return visitor->visit(this);
}

std::shared_ptr<void> lox::Function::accept(StatementVisitor* visitor)
{
	return visitor->visit(this);
}

std::shared_ptr<void> lox::IfStatement::accept(StatementVisitor* visitor)
{
	return visitor->visit(this);
}

std::shared_ptr<void> lox::Print::accept(StatementVisitor* visitor)
{
	return visitor->visit(this);
}

std::shared_ptr<void> lox::ReturnStatement::accept(StatementVisitor* visitor)
{
	return visitor->visit(this);
}

std::shared_ptr<void> lox::Var::accept(StatementVisitor* visitor)
{
	return visitor->visit(this);
}

std::shared_ptr<void> lox::WhileStatement::accept(StatementVisitor* visitor)
{
	return visitor->visit(this);
}
