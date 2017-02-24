#ifndef _EXPRESSION_H_
#define _EXPRESSION_H_

#include <string>
#include <vector>

enum AtomType { None, Boolean, Number, Symbol };
struct Atom {
	AtomType type;
	bool boolVal;
	double numberVal;
	std::string symbolVal;
};

class Expression {
private:
	Atom currAtom;
	std::vector<Expression> childVector;
	
public:
	// Default construct an Expression of type None
	Expression();

	// Construct an Expression with a single Boolean atom with value
	Expression(bool value);

	// Construct an Expression with a single Number atom with value
	Expression(double value);

	// Construct an Expression with a single Symbol atom with value
	Expression(const std::string & value);

	// Equality operator for two Expressions, two expressions are equal if the have the same 
	// type, atom value, and number of arguments
	bool operator==(const Expression & exp) const noexcept;

	//getters
	AtomType getType();
	int getExpVectorSize();
	double getNumberValue();
	bool getBooleanValue();
	std::string getSymbolValue();
	std::vector<Expression> getArgs();

	void append(Expression exp);

	void toString();
};
#endif