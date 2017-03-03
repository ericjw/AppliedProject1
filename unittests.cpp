#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"
#include "tokenize.hpp"
#include "expression.hpp"
#include "interpreter.hpp"

TEST_CASE("tests tokenizer", "[tokenize]") {
	Tokenizer tok;
	std::string tests[] = {
		"(+ a ( - 4 ))",
		"(if (< a b) b a)",
		"(begin (define r 10) (* pi (* r r)))",
		""
	};
	
	std::list<std::string> testList = {
    	"(", "begin", "(", "define", "r", "10", ")", "(", "*", "pi", "(", "*", "r", "r", ")", ")", ")" 
	};

	std::list<std::string> outputList = tok.tokenize(tests[2]);

	REQUIRE(outputList == testList);

	testList = {"(", "begin", "(", "define"};
	//std::cout << "HERE ";
	outputList = tok.tokenize("(begin (define ;r 10) (* pi (* r r)))");

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

TEST_CASE("tests interpreter ast creation", "[interpreter]") {

	Interpreter inter;
	Expression root;
	std::list<std::string> test;

	//test readtokens directly
	test = {"(", "+", "a", "(", "+", "-", "(", "4", ")", "4", ")", ")", ")"};
	root = inter.readTokens(test);
	REQUIRE(root.getExpVectorSize() == 2);
	test = { "(", "+", "a", "(", "+", "-", "(", "4", ")", "4", ")", ")" };
	REQUIRE(inter.readTokens(test).getExpVectorSize() == 2);

	//test exceptions from parse
	std::istringstream excep("((((((if (< a b) b a)");
	REQUIRE(!inter.parse(excep));
	excep.str("(if (< a b) b a))))))"); //no exception is thrown								
	REQUIRE(!inter.parse(excep));
	excep.str("( )");
	REQUIRE(!inter.parse(excep));
	excep.str("");
	REQUIRE(!inter.parse(excep));
	
	//test parse
	std::istringstream is("(if (< a b) b a)"); 
	REQUIRE(inter.parse(is));
	root = inter.getAST();
	REQUIRE(root.getSymbolValue() == "if");
	std::vector<Expression> args = root.getArgs();
	REQUIRE(args.at(0).getSymbolValue() == "<");
	REQUIRE(args.at(1).getSymbolValue() == "b");
	REQUIRE(args.at(2).getSymbolValue() == "a");
	args = args.at(0).getArgs();
	REQUIRE(args.at(0).getSymbolValue() == "a");
	REQUIRE(args.at(1).getSymbolValue() == "b");
	
}

TEST_CASE("tests interpreter eval", "[interpreter]") {
	std::istringstream is("(if (>= pi 2) pi 4)"); // works with <, >, <=, >=
	Interpreter inter;
	inter.parse(is);
	Expression tmp = inter.eval();
	//std::cout << "---------> if stmnt " << tmp.getNumberValue() << std::endl;

	is.str("(begin (define r 10) (* pi (* r r)))"); // works
	inter.parse(is);
	tmp = inter.eval();
	REQUIRE(tmp.getType() == AtomType::Number);
	REQUIRE(tmp.getNumberValue() == 100 * std::atan2(0, -1));
	Expression tmpEq = Expression(100 * std::atan2(0, -1));
	REQUIRE(tmpEq == tmp);
	//std::cout << "---------> longer " << tmp.getNumberValue() << std::endl;

	is.str("(begin (define a 1)(define b pi)(if (< a b) b a))");
	inter.parse(is);
	tmp = inter.eval();
	//std::cout << "---------> all special " << tmp.getNumberValue() << std::endl;
}

TEST_CASE("tests environment", "[environment]") {
	Environment env;
	env.initialize();
	Interpreter inter;

	Expression tmp = env.insert("test", Expression(true));
	REQUIRE(env.varExists("test"));
	REQUIRE(env.getVal("test") == tmp);
	REQUIRE(env.getVal("pi") == Expression(std::atan2(0, -1)));

	REQUIRE(env.getFunc("DNE") == nullptr);
	REQUIRE(typeid(env.getFunc("+")) == typeid(Environment::funcPtr));

	//test all functions 

	//and
	std::istringstream is("(and True False (< 1 2))");
	inter.parse(is);
	REQUIRE(!inter.eval().getBooleanValue());

	//or
	is.str("(or True False (< 1 2))");
	inter.parse(is);
	REQUIRE(inter.eval().getBooleanValue());

	//less
	is.str("(< 2 1)");
	inter.parse(is);
	REQUIRE(!inter.eval().getBooleanValue());
}