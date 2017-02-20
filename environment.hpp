#ifndef _ENVIRONMENT_H_
#define _ENVIRONMENT_H_

#include <unordered_map>
using std::unordered_map;

typedef void(*ScriptFunction)(void);
unordered_map < std::string, ScriptFunction > env;

bool not (bool arg);
bool and (bool arg1, bool arg2);
bool or (bool arg1, bool arg2);

bool less(double arg1, double arg2);

bool less_equal(double arg1, double arg2);
bool greater(double arg1, double arg2);

bool greater_equal(double arg1, double arg2);
bool equal(double arg1, double arg2);

double plus(double arg1, double arg2);

double minus(double arg1, double arg2);

double neg(double arg1);

double mult(double arg1, double arg2);

double div(double arg1, double arg2);

#endif