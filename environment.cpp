#include "environment.hpp"
#include <iostream>

Expression Environment::insert(std::string name, Expression newVar) {
	vars.insert({name, newVar});
	return newVar;
}

void Environment::initialize() {
	env = { { "not", (&Environment::notFunc) },{ "and", (&Environment::andFunc) },{ "or", (&Environment::orFunc) },{ "<", (&Environment::lessFunc) },
	{ "<=", (&Environment::less_equalFunc) },{ ">", (&Environment::greaterFunc) },{ ">=", (&Environment::greater_equalFunc) },{ "=", (&Environment::equalFunc) },
	{ "+", (&Environment::plusFunc) },{ "-", (&Environment::minusFunc) },{ "*", (&Environment::multFunc) },{ "/", (&Environment::divFunc) } };
	vars = { { "pi", Expression(std::atan2(0, -1)) } };
}

bool Environment::varExists(std::string varName) {
	auto search = vars.find(varName);
	return search != vars.end();
}

Expression Environment::getVal(std::string arg) {
	return vars.find(arg)->second;
}

Environment::funcPtr Environment::getFunc(std::string arg) {
	auto search = env.find(arg);
	if (search == env.end()) {
		return nullptr;
	}
	else
	{
		return search->second;
	}
}

Expression Environment::notFunc(Expression exp) {
	if (exp.getArgs().size() != 1) {
		throw InterpreterSemanticError("Invalid number of arguments to not");
	}
	return Expression(!exp.getArgs().at(0).getBooleanValue());
}

Expression Environment::andFunc(Expression exp) {
	if (exp.getArgs().size() < 2) {
		throw InterpreterSemanticError("Invalid number of arguments to and");
	}
	bool value = true;
	for (auto iter : exp.getArgs()) {
		value = value && iter.getBooleanValue();
	}
	return Expression(value);
}

Expression Environment::orFunc(Expression exp) {
	if (exp.getArgs().size() < 2) {
		throw InterpreterSemanticError("Invalid number of arguments to or");
	}
	bool value = exp.getArgs().front().getBooleanValue();
	for (auto iter : exp.getArgs()) {
		value = value || iter.getBooleanValue();
	}
	return Expression(value);
}

Expression Environment::lessFunc(Expression exp) {
	if (exp.getArgs().size() != 2) {
		throw InterpreterSemanticError("Invalid number of arguments to <");
	}
	std::vector<Expression> tmp = exp.getArgs();
	bool value = tmp.front().getNumberValue() < tmp.at(1).getNumberValue();
	return Expression(value);
}

Expression Environment::greaterFunc(Expression exp) {
	if (exp.getArgs().size() != 2) {
		throw InterpreterSemanticError("Invalid number of arguments to >");
	}
	std::vector<Expression> tmp = exp.getArgs();
	bool value = tmp.front().getNumberValue() > tmp.at(1).getNumberValue();
	return Expression(value);
}

Expression Environment::less_equalFunc(Expression exp) {
	if (exp.getArgs().size() != 2) {
		throw InterpreterSemanticError("Invalid number of arguments to <");
	}
	std::vector<Expression> tmp = exp.getArgs();
	bool value = tmp.front().getNumberValue() <= tmp.at(1).getNumberValue();
	return Expression(value);
}

Expression Environment::greater_equalFunc(Expression exp) {
	if (exp.getArgs().size() != 2) {
		throw InterpreterSemanticError("Invalid number of arguments to >=");
	}
	std::vector<Expression> tmp = exp.getArgs();
	bool value = tmp.front().getNumberValue() >= tmp.at(1).getNumberValue();
	return Expression(value);
}

Expression Environment::equalFunc(Expression exp) {
	if (exp.getArgs().size() != 2) {
		throw InterpreterSemanticError("Invalid number of arguments to <=");
	}
	std::vector<Expression> tmp = exp.getArgs();
	bool value = tmp.front().getNumberValue() == tmp.at(1).getNumberValue();
	return Expression(value);
}


Expression Environment::plusFunc(Expression exp) {
	if (exp.getArgs().size() < 2) {
		throw InterpreterSemanticError("Invalid number of arguments to +");
	}
	double value = 0;
	for (auto iter : exp.getArgs()) {
		value += iter.getNumberValue();
	}
	return Expression(value);
}

Expression Environment::minusFunc(Expression exp) {
	std::vector<Expression> tmp = exp.getArgs();
	if (tmp.size() == 2) {
		double value = tmp.front().getNumberValue() - tmp.at(1).getNumberValue();
		return Expression(value);
	}
	else if (tmp.size() == 1) {
		return Expression(-tmp.front().getNumberValue());
	}
	else
		throw InterpreterSemanticError("Invalid number of arguments to -");
}

Expression Environment::multFunc(Expression exp) {
	if (exp.getArgs().size() < 2) {
		throw InterpreterSemanticError("Invalid number of arguments to *");
	}
	double value = 1.0;
	for (auto iter : exp.getArgs()) {
		value *= iter.getNumberValue();
	}
	return Expression(value);
}

Expression Environment::divFunc(Expression exp) {
	if (exp.getArgs().size() != 2) {
		throw InterpreterSemanticError("Invalid number of arguments to /");
	}
	std::vector<Expression> tmp = exp.getArgs();
	double value = tmp.front().getNumberValue() / tmp.at(1).getNumberValue();
	return Expression(value);
}