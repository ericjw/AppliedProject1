#ifndef _ENVIRONMENT_H_
#define _ENVIRONMENT_H_
#include "expression.hpp"

#include <unordered_map>
#include <cmath>
using std::unordered_map;

typedef Expression(*functionptr)(Expression);

//function declarations
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
Expression piFunc(Expression arg);

//function pointers
typedef Expression(*funcPtr)(Expression);

unordered_map < std::string, functionptr > env;
unordered_map < std::string, Expression > vars;
#endif