#include "Interpreter.h"
#include <iostream>

std::shared_ptr<lox::Interpreter*> lox::Interpreter::instance = nullptr;



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

std::shared_ptr<lox::Value> lox::Interpreter::evaluate(Expression* expression)
{
	return std::static_pointer_cast<Value>(expression->accept(this));
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
		value.vtype = NIL_PTR;
		value.value = nullptr;
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
