#include "environment.hpp"

Expression notFunc(Expression exp) {
	return Expression(!(exp.getArgs().front().getBooleanValue()));
}

Expression andFunc(Expression exp) {
	return Expression();
}

Expression orFunc(Expression exp) {
	return Expression();
}

Expression lessFunc(Expression exp) {
	return Expression();
}

Expression greaterFunc(Expression exp) {
	return Expression();
}

Expression less_equalFunc(Expression exp) {
	return Expression();
}

Expression greater_equalFunc(Expression exp) {
	return Expression();
}

Expression equalFunc(Expression exp) {
	return Expression();
}

Expression plusFunc(Expression exp) {
	return Expression();
}

Expression negFunc(Expression exp) {
	return Expression();
}

Expression minusFunc(Expression exp) {
	return Expression();
}

Expression multFunc(Expression exp) {
	return Expression();
}

Expression divFunc(Expression exp) {
	return Expression();
}

Expression piFunc(Expression exp) {
	return Expression();
}