#include "interpreter.hpp"
#include "interpreter_semantic_error.hpp"

#include <iostream>
#include <cstdlib>
#include <vector>
#include <stdexcept>
#include <cctype>
#include <sstream>
#include <algorithm>

Interpreter::Interpreter() {
	envir.initialize();
}

Expression Interpreter::readTokens(std::list<std::string>& tokens) {
	std::string left = "(";
	std::string right = ")";
	Expression exp;

	if (tokens.size() == 0)
		throw std::logic_error("unexpected eof");
	
	std::string token = tokens.front();
	tokens.pop_front();

	if (left == token){
		token = tokens.front();
		if (token == left || token == right)
			throw std::logic_error("invalid paren");



		if (token == "True") {
			exp = Expression(true);
		}
		else if (token == "False") {
			exp = Expression(false);
		}
		else {
			try {
				std::stringstream value(token);
				double d;
				value >> d;
				if (value.fail()) { //??
									//std::cout << "!!!!!!!!!!!!" << std::endl;
					throw std::logic_error("not a num");
				}
				if (value.eof())
					exp = Expression(d);
				else
					throw std::invalid_argument("bad number string");
			}
			catch (std::invalid_argument e) {
				throw e;
			}
			catch (...) {
				exp = Expression(token);
			}
		}

		tokens.pop_front();
		while (tokens.front() != right) { 
			exp.append(readTokens(tokens));
		}
		tokens.pop_front(); //pop )
		return exp;
	}
	else if (right == token) {
		//std::cout << "!!!!!!!!!!!!!!!!!!!";
		throw std::logic_error("unexpected )");
	}
	else {
		if (token == "True") {
			return Expression(true);
		}
		else if (token == "False") {
			return Expression(false);
		}
		try {
			std::stringstream value(token);
			double d;
			value >> d;
			if (value.fail()) { //??
				//std::cout << "!!!!!!!!!!!!" << std::endl;
				throw std::logic_error("not a num");
			}
			if (value.eof())
				return Expression(d);
			else
				throw std::invalid_argument("bad number string");
		} catch (std::invalid_argument e) {
			throw e;
		} catch (...) {
			return Expression(token);
		}
		
	}
}

bool Interpreter::parse(std::istream & expression) noexcept {
	std::string tmpString((std::istreambuf_iterator<char>(expression)),
		std::istreambuf_iterator<char>());

	std::list<std::string> tmpSizeList = tok.tokenize(tmpString);
	int left = std::count(tmpSizeList.begin(), tmpSizeList.end(), "(");
	int right = std::count(tmpSizeList.begin(), tmpSizeList.end(), ")");
	if (left != right)
		return false;
	std::string leftParan = "(";
	if (tmpSizeList.size() != 0 && tmpSizeList.front() != leftParan) {
		return false;
	}
	try {
		ast = readTokens(tmpSizeList);
		if (tmpSizeList.size() != 0) {
			return false;
		}
		return true;
	}
	catch (...) {
		return false;
	}
}

Expression Interpreter::getAST() {
	return ast;
}



Expression Interpreter::eval() {
	return recurseEval(ast);
}

Expression Interpreter::recurseEval(Expression curr) {
	//is a variable lookup or constant value
	if (curr.getArgs().size() == 0) {
		if (curr.getType() == AtomType::Symbol) {
			if (envir.varExists(curr.getSymbolValue())) {
				return envir.getVal(curr.getSymbolValue());
			}
			else {
				throw InterpreterSemanticError("Symbol not found");
			}
		}
		else if (curr.getType() == AtomType::Boolean){
			return Expression(curr.getBooleanValue());
		}
		else if (curr.getType() == AtomType::Number) {
			return Expression(curr.getNumberValue());
		}
	}
	//is a special case
	else if (curr.getType() == AtomType::Symbol) {
		Expression answers;
		std::vector<Expression> tmpArgs = curr.getArgs();

		if (curr.getSymbolValue() == "if") {
			if (curr.getArgs().size() != 3) {
				throw InterpreterSemanticError("Invalid number of arguments to if statement");
			}
			else{
				Expression tmp = recurseEval(tmpArgs.at(0));
				if (tmp.getType() != AtomType::Boolean) {
					throw InterpreterSemanticError("First arg to if statement does not evaluate to boolean");
				}
				else if (tmp.getBooleanValue()) {
					return recurseEval(tmpArgs.at(1));
				}
				else {
					return recurseEval(tmpArgs.at(2));
				}
			}
		}
		else if (curr.getSymbolValue() == "define") {
			if (curr.getArgs().size() != 2) {
				throw InterpreterSemanticError("Invalid number of arguments to define statement");
			}
			else if (tmpArgs.front().getSymbolValue() == "if" || 
					tmpArgs.front().getSymbolValue() == "define" ||
					tmpArgs.front().getSymbolValue() == "begin" ||
					envir.varExists(tmpArgs.front().getSymbolValue())) {
				throw InterpreterSemanticError("Cannot redefine a symbol");
			}
			else {
				return envir.insert(tmpArgs.front().getSymbolValue(), recurseEval(tmpArgs.back()));
			}
		}
		else if (curr.getSymbolValue() == "begin") {
			std::vector<Expression> children;
			for (auto iter : tmpArgs) {
				children.push_back(recurseEval(iter));
			}
			return children.back();
		}

		//normal eval of children
		else {
			for (auto iter : tmpArgs) {
				answers.append(recurseEval(iter));
			}

		}
		//function call
		Environment::funcPtr function = envir.getFunc(curr.getSymbolValue());
		if (function == nullptr) {
			throw InterpreterSemanticError("No such procedure");
		}
		else {
			return (envir.*function)(answers);
		}
	}
}