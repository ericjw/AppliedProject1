#include "interpreter.hpp"
#include "expression.hpp"
#include <fstream>
#include <iostream>

using std::ifstream;
using std::cout;
using std::cin;

int main(int argc, char* argv[])
{
	Interpreter inter;
	if (argc == 1) {
		while (!cin.eof()) {
			cout << "vtscript>";
			std::string in;
			std::getline(cin, in);
			cout << in << std::endl;
			
			//inter.parse(cin);
			//inter.eval();
			//Expression tmp = inter.getAST();
			//std::cout << "(";
			//tmp.toString();
			//std::cout << ")";
		}
	}
	else if (argc == 2) {
		std::string line;
		std::ifstream file(argv[1]);
		while (std::getline(file, line))
		{
			std::istringstream iss(line);
			inter.parse(iss);
			inter.eval();
		}
		Expression root = inter.getAST();
		root.toString();
	}
	else if (argc == 3) {
		std::istringstream ss(argv[2]);
		if (argv[1] == "-e") {
			if (inter.parse(ss) == false) {
				std::cerr << "Error: Invalid Expression. Could not parse." << std::endl;
				return EXIT_FAILURE;
			}
			inter.eval();
		}
	}
	else {
		//invalid arguments
	}

}