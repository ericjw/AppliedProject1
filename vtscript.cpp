#include "interpreter.hpp"
#include "expression.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

using std::ifstream;
using std::cout;
using std::cin;

int main(int argc, char* argv[])
{
	if (argc == 1) {
		Expression tmp;
		Interpreter inter;
		while (!cin.eof()) {
			cout << "vtscript> ";
			std::string express;
			std::getline(cin, express);

			std::istringstream iss(express);
			if (!inter.parse(iss)) {
				std::cout << "Error: Invalid Expression. Could not parse." << std::endl;
				inter = Interpreter();
			}
			else {
				try {
					Expression tmp = inter.eval();
					std::cout << "(";
					if (tmp.getType() == AtomType::Symbol) {
						std::cout << tmp.getSymbolValue();
					}
					else if (tmp.getType() == AtomType::Number) {
						std::cout << tmp.getNumberValue();
					}
					else {
						if (tmp.getBooleanValue())
							std::cout << "True";
						else
							std::cout << "False";
					}
					std::cout << ")" << std::endl;
				}
				catch (InterpreterSemanticError e) {
					std::cout << "Error: " << e.what() << std::endl;
					inter = Interpreter();
				}
			}
		}
	}
	else if (argc == 2) {
		std::string fname(argv[1]);
		std::ifstream ifs(fname);

		if (!ifs.good()) {
			std::cout << "Error: Invalid file" << std::endl;
			return EXIT_FAILURE;
		}
		
		Interpreter inter;
		if (!inter.parse(ifs)) {
			std::cout << "Error: Invalid Expression. Could not parse." << std::endl;
			inter = Interpreter();
			return EXIT_FAILURE;
		}
		else {
			try {
				Expression tmp = inter.eval();
				std::cout << "(";
				if (tmp.getType() == AtomType::Symbol) {
					std::cout << tmp.getSymbolValue();
				}
				else if (tmp.getType() == AtomType::Number) {
					std::cout << tmp.getNumberValue();
				}
				else {
					if (tmp.getBooleanValue())
						std::cout << "True";
					else
						std::cout << "False";
				}
				std::cout << ")" << std::endl;
			}
			catch (InterpreterSemanticError e) {
				std::cout << "Error: " << e.what() << std::endl;
				inter = Interpreter();
				return EXIT_FAILURE;
			}
		}
		return EXIT_SUCCESS;
	}
	else if (argc == 3) {
		if (std::string(argv[1]) != std::string("-e")) {
			std::cout << "Error: Invalid flag" << std::endl;
			return EXIT_FAILURE;
		}
		Interpreter inter;
		std::string express(argv[2]);

		std::istringstream iss(express);
		if (!inter.parse(iss)) {
			std::cout << "Error: Invalid Expression. Could not parse." << std::endl;
			inter = Interpreter();
			return EXIT_FAILURE;
		}
		else {
			try {
				Expression tmp = inter.eval();
				std::cout << "(";
				if (tmp.getType() == AtomType::Symbol) {
					std::cout << tmp.getSymbolValue();
				}
				else if (tmp.getType() == AtomType::Number) {
					std::cout << tmp.getNumberValue();
				}
				else {
					if (tmp.getBooleanValue())
						std::cout << "True";
					else
						std::cout << "False";
				}
				std::cout << ")" << std::endl;
			}
			catch (InterpreterSemanticError e) {
				std::cout << "Error: " << e.what() << std::endl;
				inter = Interpreter();
				return EXIT_FAILURE;
			}
		}
		return EXIT_SUCCESS;
	}
	else {
		std::cout << "Error: Invalid number of arguments to program" << std::endl;
	}

}