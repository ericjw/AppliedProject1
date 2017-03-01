#ifndef _ENVIRONMENT_H_
#define _ENVIRONMENT_H_
#include "expression.hpp"

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
	Expression notFunc(Expression arg);
	Expression andFunc(Expression arg);
	Expression orFunc(Expression arg);
	Expression lessFunc(Expression arg);
	Expression greaterFunc(Expression arg);
	Expression less_equalFunc(Expression arg);
	Expression greater_equalFunc(Expression arg);
	Expression equalFunc(Expression arg);
	Expression plusFunc(Expression arg);
	Expression negFunc(Expression arg);
	Expression minusFunc(Expression arg);
	Expression multFunc(Expression arg);
	Expression divFunc(Expression arg);
};
#endif