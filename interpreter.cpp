#include "interpreter.hpp"

#include <iostream>
#include <cstdlib>

Interpreter::Interpreter() {
	//default env()
}

Expression Interpreter::readTokens(std::list<std::string> & tokens) {
	std::string left = "(";
	std::string right = ")";
	Expression exp;
	if (tokens.size() == 0)
		throw "unexpected EOF";
	std::string token = tokens.front();
	tokens.pop_front();
	if (left == token){
		token = tokens.front();
		exp =  Expression(token);
		tokens.pop_front();
		while (tokens.front() != right) {
			exp.append(readTokens(tokens));
		}
		tokens.pop_front();
		return exp;
	}
	else if (")" == token)
		throw "unexpected )";
	else {
		if (token == "True")
			return Expression(true);
		else if (token == "False")
			return Expression(false);
		else {
			try {
				return Expression(std::stod(token));
			}
			catch (...) {
				return Expression(token);
			}
		}
	}
}

bool Interpreter::parse(std::istream & expression) noexcept {
	std::string tmpString(std::istreambuf_iterator<char>(expression), {});
	
	try {
		ast = readTokens(tokenize(tmpString));
		return true;
	}
	catch (...){
		return false;
	}
}

Expression Interpreter::getAST() {
	return ast;
}



Expression Interpreter::eval() {
	return Expression(); //placeholder
}