#include "interpreter.hpp"
#include "interpreter_semantic_error.hpp"

#include <iostream>
#include <cstdlib>
#include <vector>
#include <stdexcept>

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
		if (token == left)
			throw std::logic_error("invalid paren");
		exp = Expression(token);
		tokens.pop_front();
		while (tokens.front() != right) {
			exp.append(readTokens(tokens));
		}
		tokens.pop_front(); //pop )
		return exp;
	}
	else if (right == token) {
		throw std::logic_error("unexpected )");
	}
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
		ast = readTokens(tok.tokenize(tmpString));
		return true;
	}
	catch (...) {
		//std::cout << "ERROR CAUGHT";
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
				return curr;
			}
		}
		else {
			return curr;
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
					tmpArgs.front().getSymbolValue() == "begin") {
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
			throw InterpreterSemanticError("Invalid symbol");
		}
		else {
			return (envir.*function)(answers);
		}

	}

	else {
		throw InterpreterSemanticError("asdf");
	}
}