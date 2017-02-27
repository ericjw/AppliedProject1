#include "environment.hpp"

void insert(std::string name, Expression newVar) {
	vars.insert({name, newVar});
}

void initialize() {
	env = { { "not", (notFunc) },{ "and", (andFunc) },{ "or", (orFunc) },{ "<", (lessFunc) },
	{ "<=", (less_equalFunc) },{ ">", (greaterFunc) },{ ">=", (greater_equalFunc) },{ "=", (equalFunc) },{ "+", (plusFunc) },{ "-", (minusFunc) },
	{ "*", (multFunc) },{ "/", (divFunc) },{ "pi", (piFunc) } };
}

Expression notFunc(Expression exp) {
	return Expression(!(exp.getArgs().front().getBooleanValue()));
}

Expression andFunc(Expression exp) {
	bool value = true;
	for (auto iter : exp.getArgs()) {
		value = value && iter.getBooleanValue();
	}
	return Expression(value);
}

Expression orFunc(Expression exp) {
	bool value = true;
	for (auto iter : exp.getArgs()) {
		value = value || iter.getBooleanValue();
	}
	return Expression(value);
}

Expression lessFunc(Expression exp) {
	std::vector<Expression> tmp = exp.getArgs();
	bool value = tmp.front().getNumberValue() < tmp.at(1).getNumberValue();
	return Expression(value);
}

Expression greaterFunc(Expression exp) {
	std::vector<Expression> tmp = exp.getArgs();
	bool value = tmp.front().getNumberValue() > tmp.at(1).getNumberValue();
	return Expression(value);
}

Expression less_equalFunc(Expression exp) {
	std::vector<Expression> tmp = exp.getArgs();
	bool value = tmp.front().getNumberValue() <= tmp.at(1).getNumberValue();
	return Expression(value);
}

Expression greater_equalFunc(Expression exp) {
	std::vector<Expression> tmp = exp.getArgs();
	bool value = tmp.front().getNumberValue() >= tmp.at(1).getNumberValue();
	return Expression(value);
}

Expression equalFunc(Expression exp) {
	std::vector<Expression> tmp = exp.getArgs();
	bool value = tmp.front().getNumberValue() == tmp.at(1).getNumberValue();
	return Expression(value);
}


Expression plusFunc(Expression exp) {
	double value = 0;
	for (auto iter : exp.getArgs()) {
		value += iter.getNumberValue();
	}
	return Expression(value);
}

Expression negFunc(Expression exp) {
	return Expression(-exp.getArgs().front().getNumberValue());
}

Expression minusFunc(Expression exp) {
	std::vector<Expression> tmp = exp.getArgs();
	double value = tmp.front().getNumberValue() - tmp.at(1).getNumberValue();
	return Expression(value);
}

Expression multFunc(Expression exp) {
	double value = 0;
	for (auto iter : exp.getArgs()) {
		value *= iter.getNumberValue();
	}
	return Expression(value);
}

Expression divFunc(Expression exp) {
	std::vector<Expression> tmp = exp.getArgs();
	double value = tmp.front().getNumberValue() / tmp.at(1).getNumberValue();
	return Expression(value);
}

Expression piFunc(Expression exp) {
	return Expression(std::atan2(0,-1));
}