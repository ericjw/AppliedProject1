#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"
#include "tokenize.hpp"
#include "expression.hpp"
#include "interpreter.hpp"


TEST_CASE("tests tokenizer", "[tokenize]") {
	std::string tests[] = {
		"(+ a ( - 4 ))",
		"(if (< a b) b a)",
		"(begin (define r 10) (* pi (* r r)))",
		""
	};

	std::list<std::string> testList = {
		"(", "begin", "(", "define", "r", "10", ")", "(", "*", "pi", "(", "*", "r", "r", ")", ")", ")" 
	};
	std::list<std::string> outputList = tokenize(tests[2]);

	REQUIRE(outputList == testList);
}

TEST_CASE("tests expression", "[expression]") {
	bool tester;
	Expression exp1;
	Expression exp2;
	Expression exp3;
	REQUIRE(exp1.getType() == AtomType::None);
	REQUIRE(exp1 == exp2);
	exp1 = Expression(true);
	tester = (exp1 == exp2);
	REQUIRE(tester == false);

	exp3 = Expression(false);
	REQUIRE(exp3.getType() == AtomType::Boolean);
	exp2 = Expression(true);
	REQUIRE(exp1 == exp2);
	exp1.append(exp2);
	REQUIRE(exp1 == exp2);
	tester = (exp1 == exp3);
	REQUIRE(tester == false);

	std::string symbolTest = "Test";
	exp3 = Expression(symbolTest);
	REQUIRE(exp3.getType() == AtomType::Symbol);
	tester = (exp3 == exp2);
	REQUIRE(tester == false);
	exp2 = Expression(symbolTest);
	REQUIRE(exp2 == exp3);
	symbolTest = "Test2";
	exp2 = Expression(symbolTest);
	tester = (exp2 == exp3);
	REQUIRE(tester == false);

	exp3 = Expression(1.0);
	REQUIRE(exp3.getType() == AtomType::Number);
	exp2 = Expression(2.3);
	exp1 = Expression(2.3);
	REQUIRE(exp1 == exp2);
	tester = (exp3 == exp2);
	REQUIRE(tester == false);
	
}


TEST_CASE("tests interpreter", "[interpreter]") {
	
	Interpreter inter;
	std::list<std::string> test = {"(", "+", "a", "(", "-", "1e4", ")", ")"};
	Expression root = inter.readTokens(test);
	REQUIRE(root.getExpVectorSize() == 2);
}
