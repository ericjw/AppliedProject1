#ifndef _ENVIRONMENT_H_
#define _ENVIRONMENT_H_
#include "expression.hpp"
#include "interpreter_semantic_error.hpp"

#include <unordered_map>
#include <cmath>
using std::unordered_map;

class Environment {
public:
	typedef Expression(Environment::*funcPtr)(Expression exp);
private:
	unordered_map < std::string, funcPtr > env;
	unordered_map < std::string, Expression > vars;
public:
	//function declarations
	funcPtr getFunc(std::string arg);
	Expression getVal(std::string arg);
	void initialize();
	Expression insert(std::string name, Expression newVar);
	bool varExists(std::string varName);
	Expression notFunc(Expression exp);
	Expression andFunc(Expression exp);
	Expression orFunc(Expression exp);
	Expression lessFunc(Expression exp);
	Expression greaterFunc(Expression exp);
	Expression less_equalFunc(Expression exp);
	Expression greater_equalFunc(Expression exp);
	Expression equalFunc(Expression exp);
	Expression plusFunc(Expression exp);
	Expression minusFunc(Expression exp);
	Expression multFunc(Expression exp);
	Expression divFunc(Expression exp);
};
#endif