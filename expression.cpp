#include "expression.hpp"

Expression::Expression() {
	type = None;
}

Expression::Expression(bool value) {
	type = Boolean;
	boolVal = value;
}

Expression::Expression(double value) {
	type = Number;
	numberVal = value;
}

Expression::Expression(const std::string & value) {
	type = Symbol;
	symbolVal = value;
}

bool getBooleanValue() {
	return boolVal;
}

std::string getSymbolValue() {
	return symbolVal;
}



bool operator==(const Expression & exp) const noexcept {
	return (type == exp.type)
}