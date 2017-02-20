#include "environment.hpp"

bool not (bool arg) {
	return !arg;
}

bool and (bool arg1, bool arg2) {
	return arg1 && arg2;
}

bool or (bool arg1, bool arg2) {
	return arg1 == arg2;
}

bool less(double arg1, double arg2) {
	return arg1 < arg2;
}

bool less_equal(double arg1, double arg2) {
	return arg1 <= arg2;
}

bool greater(double arg1, double arg2) {
	return arg1 > arg2;
}

bool greater_equal(double arg1, double arg2) {
	return arg1 >= arg2;
}

bool equal(double arg1, double arg2) {
	return arg1 == arg2;
}

double plus(double arg1, double arg2) {
	return arg1 + arg2;
}

double minus(double arg1, double arg2) {
	return arg1 - arg2;
}

double neg(double arg1) {
	return -arg1;
}

double mult(double arg1, double arg2) {
	return arg1 * arg2;
}

double div(double arg1, double arg2) {
	return arg1 / arg2;
}