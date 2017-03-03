#include "expression.hpp"

#include <iostream>
#include <cstdlib>

Expression::Expression() {
	currAtom.type = None;
}

Expression::Expression(bool value) {
	currAtom.type = Boolean;
	currAtom.boolVal = value;
}

Expression::Expression(double value) {
	currAtom.type = Number;
	currAtom.numberVal = value;
}

Expression::Expression(const std::string & value) {
	currAtom.type = Symbol;
	currAtom.symbolVal = value;
}

AtomType Expression::getType() {
	return currAtom.type;
}

bool Expression::getBooleanValue() {
	return currAtom.boolVal;
}

double Expression::getNumberValue() {
	return currAtom.numberVal;
}

std::string Expression::getSymbolValue() {
	return currAtom.symbolVal;
}

int Expression::getExpVectorSize() {
	return childVector.size();
}

void Expression::append(Expression exp) {
	childVector.push_back(exp);
}

std::vector<Expression> Expression::getArgs() {
	return childVector;
}

bool Expression::operator==(const Expression & exp) const noexcept {
	if (currAtom.type != exp.currAtom.type)
		return false;
	else if (exp.childVector.size() == exp.childVector.size()) {
		switch (currAtom.type) {
		case Boolean:
			return (currAtom.boolVal == exp.currAtom.boolVal);
			break;
		case Number:
			return (currAtom.numberVal == exp.currAtom.numberVal);
			break;
		case Symbol:
			return (currAtom.symbolVal == exp.currAtom.symbolVal);
			break;
		case None:
			return true;
		default:
			return true;
		}
	}
	else
		return false;
}
