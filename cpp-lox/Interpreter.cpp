#include "Interpreter.h"
#include <iostream>
#include "Environment.h"
#include "LoxCallable.h"
std::shared_ptr<lox::Interpreter*> lox::Interpreter::instance = nullptr;

lox::Interpreter::Interpreter() 
{
	globals = std::make_shared<Environment*>(new Environment);
	Value clock;
	clock.vtype = CALLABLE;
	clock.value = std::make_shared<LoxCallable*>(new ClockCallable);
	(*globals)->define("clock", std::make_shared<Value>(clock));
	env = globals;
}


bool lox::Interpreter::isTruthy(std::shared_ptr<Value> value)
{
	if (value->vtype == NIL_PTR) return false;
	if (value->vtype == BOOL) return std::get<bool>(value->value);
	return true;
}

bool lox::Interpreter::isEqual(std::shared_ptr<Value> left, std::shared_ptr<Value> right)
{
	if (left->vtype == NIL_PTR && right->vtype == NIL_PTR) return true;
	if (left->vtype == NIL_PTR) return false;
	if (left->vtype != right->vtype) return false;
	return left->value == right->value;
}

void lox::Interpreter::checkNumberOperand(lox::Token op, std::shared_ptr<Value> operand)
{
	if (operand->vtype == DOUBLE) return;
	throw RuntimeError(op, "Operand must be a number.");
}

void lox::Interpreter::checkNumberOperands(Token op, std::shared_ptr<Value> left, std::shared_ptr<Value> right)
{
	if (left->vtype == DOUBLE && right->vtype == DOUBLE) return;
	throw RuntimeError(op, "Operand must be a numbers.");
}

std::shared_ptr<lox::Interpreter*> lox::Interpreter::getInstance()
{
	if (Interpreter::instance == nullptr)
		Interpreter::instance = std::make_shared<Interpreter*>(new Interpreter);
	return Interpreter::instance;
}

/*
void lox::Interpreter::interpret(Expression* expression)
{
	//TODO
	try {
		std::shared_ptr<Value> value = evaluate(expression);
		if (value->vtype == NIL_PTR)
			std::cout << "nil" << std::endl;
		std::visit([](auto&& arg) { std::cout << std::boolalpha << arg << std::endl; }, value->value);
	}
	catch (const RuntimeError& e) {
		//TODO Lox.runtime
	}
	catch (const std::exception& e) {
		e.what();
	}
}
*/
std::shared_ptr<lox::Value> lox::Interpreter::evaluate(Expression* expression)
{
	return std::static_pointer_cast<Value>(expression->accept(this));
}

void lox::Interpreter::executeBlock(std::deque<StmtPtr> statements, std::shared_ptr<lox::Environment*> env)
{
	std::shared_ptr<Environment*> previous = this->env;
	try {
		this->env = env;
		for (StmtPtr stmt : statements) {
			execute(stmt);
		}
	}
	catch (const std::exception& e) {
		std::cout << e.what();
		throw e;
	}
	this->env = previous;
}

void lox::Interpreter::interpret(std::deque<StmtPtr> statements)
{
	try {
		for (StmtPtr statement : statements) {
			execute(statement);
		}
	}
	catch (const RuntimeError& e) {
		lox::runtimeError(e);
	}
}

void lox::Interpreter::execute(StmtPtr statement)
{
	(*statement)->accept(this);
}

std::shared_ptr<void> lox::Interpreter::visit(Binary* _binary)
{
	//TODO: Clean up Code
	std::shared_ptr<Value> left = evaluate(*_binary->left);
	std::shared_ptr<Value> right = evaluate(*_binary->right);
	Value value;
	switch (_binary->op.type) {
	case MINUS:
		checkNumberOperands(_binary->op, left, right);
		value.vtype = DOUBLE;
		value.value = std::get<double>(left->value) - std::get<double>(right->value);
		return std::make_shared<Value>(value);
		break;
	case PLUS:
		if (left->vtype == DOUBLE && right->vtype == DOUBLE) {
			value.vtype = DOUBLE;
			value.value = std::get<double>(left->value) + std::get<double>(right->value);
			return std::make_shared<Value>(value);
		}
		if (left->vtype == STR && right->vtype == STR) {
			value.vtype = STR;
			value.value = std::get<std::string>(left->value) + std::get<std::string>(right->value);
			return std::make_shared<Value>(value);
		}
		throw new RuntimeError(_binary->op, "Operands must be two numbers or two strings.");
		break;
	case SLASH:
		checkNumberOperands(_binary->op, left, right);
		value.vtype = DOUBLE;
		value.value = std::get<double>(left->value) / std::get<double>(right->value);
		return std::make_shared<Value>(value);
		break;
	case STAR:
		checkNumberOperands(_binary->op, left, right);
		value.vtype = DOUBLE;
		value.value = std::get<double>(left->value) * std::get<double>(right->value);
		return std::make_shared<Value>(value);
		break;
	case GREATER:
		checkNumberOperands(_binary->op, left, right);
		value.vtype = BOOL;
		value.value = std::get<double>(left->value) > std::get<double>(right->value);
		return std::make_shared<Value>(value);
		break;
	case GREATER_EQUAL:
		checkNumberOperands(_binary->op, left, right);
		value.vtype = BOOL;
		value.value = std::get<double>(left->value) >= std::get<double>(right->value);
		return std::make_shared<Value>(value);
		break;
	case LESS:
		checkNumberOperands(_binary->op, left, right);
		value.vtype = BOOL;
		value.value = std::get<double>(left->value) < std::get<double>(right->value);
		return std::make_shared<Value>(value);
		break;
	case LESS_EQUAL:
		checkNumberOperands(_binary->op, left, right);
		value.vtype = BOOL;
		value.value = std::get<double>(left->value) <= std::get<double>(right->value);
		return std::make_shared<Value>(value);
		break;
	case BANG_EQUAL:
		value.vtype = BOOL;
		value.value = !isEqual(left, right);
		return std::make_shared<Value>(value);
		break;
	case EQUAL_EQUAL:
		value.vtype = BOOL;
		value.value = isEqual(left, right);
		return std::make_shared<Value>(value);
		break;
	}

	return nullptr;
}

std::shared_ptr<void> lox::Interpreter::visit(Grouping* _grouping)
{
	return evaluate(*(_grouping->expression));
}

std::shared_ptr<void> lox::Interpreter::visit(Literal* _literal)
{
	Value value;
	if (_literal->value.type == TRUE || _literal->value.type == FALSE) {
		value.vtype = BOOL;
		value.value = (_literal->value.type == TRUE) ? true : false;
	}
	else if (_literal->value.type == NUMBER) {
		value.vtype = DOUBLE;
		value.value = std::stod(_literal->value.value);
	} else if (_literal->value.type == lox::TokenType::STRING) {
		value.vtype = STR;
		value.value = _literal->value.value;
	} else if (_literal->value.type == NIL) {
		value.vtype = NIL_PTR; //?
	}
	return std::make_shared<Value>(value);
}

std::shared_ptr<void> lox::Interpreter::visit(Unary* _unary)
{
	std::shared_ptr<lox::Value> right = evaluate(*_unary->right);
	switch (_unary->op.type) {
	case MINUS: {
		double temp = std::get<double>(right->value);
		right->value = temp * -1;
		return right;
	}
		break;
	case BANG:
		Value val;
		val.vtype = BOOL;
		val.value = !isTruthy(right);
		return std::make_shared<Value>(val);
		break;
	}
	return nullptr;
}

std::shared_ptr<void> lox::Interpreter::visit(Assign* _assign)
{
	std::shared_ptr<Value> value = evaluate(*_assign->value);
	(*env)->assign(_assign->name, value);
	return value;
}

std::shared_ptr<void> lox::Interpreter::visit(Call* _call)
{
	std::shared_ptr<Value> value = evaluate(*_call->calle);
	std::deque<std::shared_ptr<Value>> args;
	for (ExprPtr arg : _call->arguments) {
		args.push_back(evaluate(*arg));
	}
	if (value->vtype != CALLABLE) {
		throw RuntimeError(_call->paren, "Can only call functions and classes.");
	}
	std::shared_ptr<LoxCallable*> func = std::get <std::shared_ptr<LoxCallable*>>(value->value);
	if (args.size() != (*func)->arity()) {
		throw RuntimeError(_call->paren, "Expected " + std::to_string((*func)->arity()) + " arguements but got " + std::to_string(args.size()) + ".");
	}
	return (*func)->call(this, args);
}

std::shared_ptr<void> lox::Interpreter::visit(Logical* _logical)
{
	std::shared_ptr<Value> left = evaluate(*_logical->left);
	if (_logical->op.type == TokenType::OR) {
		if (isTruthy(left)) return left;
	}
	else {
		if (!isTruthy(left)) return left;
	}
	return evaluate(*_logical->right);
}

std::shared_ptr<void> lox::Interpreter::visit(Variable* _variable)
{
	std::shared_ptr<Value> value = (*env)->get(_variable->name);
	return value;
}

void lox::Interpreter::visit(ExpressionStatement* _expression)
{
	evaluate(*_expression->expression);
}

void lox::Interpreter::visit(Print* _print)
{
	std::shared_ptr<Value> value = std::static_pointer_cast<Value>(evaluate(*_print->expression));
	if (value->vtype == NIL_PTR)
		std::cout << "nil" << std::endl;
	else
		std::visit([](auto&& arg) { std::cout << std::boolalpha << arg << std::endl; }, value->value);
}

void lox::Interpreter::visit(Block* _block)
{
	executeBlock(_block->statements, std::make_shared<Environment*>(new Environment(this->env)));
}

void lox::Interpreter::visit(Function* _function)
{
	std::shared_ptr<LoxCallable*> function = std::make_shared<LoxCallable*>( new LoxFunction(std::make_shared<Function*>(_function)));
	std::shared_ptr<Value> func = std::make_shared<Value>();
	func->vtype = CALLABLE;
	func->value = function;
	(*env)->define(_function->name.lexeme, func);
	
}

void lox::Interpreter::visit(IfStatement* _if)
{
	if (isTruthy(evaluate(*_if->condition))) {
		execute(_if->thenBranch);
	}
	else if (_if->elseBranch != nullptr) {
		execute(_if->elseBranch);
	}
}

void lox::Interpreter::visit(Var* _var)
{
	std::shared_ptr<Value> value = nullptr;
	if (_var->initializer != nullptr) {
		value = evaluate(*_var->initializer);
	}
	(*env)->define(_var->name.lexeme, value);
}

void lox::Interpreter::visit(WhileStatement* _while)
{
	while (isTruthy(evaluate(*_while->condition))) {
		execute(_while->body);
	}
}
