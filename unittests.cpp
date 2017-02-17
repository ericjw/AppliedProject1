#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"
#include "tokenize.hpp"


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