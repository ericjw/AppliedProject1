#ifndef _ENVIRONMENT_H_
#define _ENVIRONMENT_H_
#include "expression.hpp"

#include <unordered_map>
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
extern Expression(*notPtr)(Expression) = &notFunc;
extern Expression(*andPtr)(Expression) = &andFunc;
extern Expression(*orPtr)(Expression) = &orFunc;
extern Expression(*lessPtr)(Expression) = &lessFunc;
extern Expression(*greaterPtr)(Expression) = &greaterFunc;
extern Expression(*less_equalPtr)(Expression) = &less_equalFunc;
extern Expression(*greater_equalPtr)(Expression) = &greater_equalFunc;
extern Expression(*equalPtr)(Expression) = &equalFunc;
extern Expression(*plusPtr)(Expression) = &plusFunc;
extern Expression(*negPtr)(Expression) = &negFunc;
extern Expression(*minusPtr)(Expression) = &minusFunc;
extern Expression(*multPtr)(Expression) = &multFunc;
extern Expression(*divPtr)(Expression) = &divFunc;
extern Expression(*piPtr)(Expression) = &piFunc;

unordered_map < std::string, functionptr > env =  { { "not", (*notPtr) } };
#endif