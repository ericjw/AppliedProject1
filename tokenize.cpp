#include "tokenize.hpp"

//tokenizes input given as a string
std::list<std::string> Tokenizer::tokenize(std::string input) {
	//scrub comments
	/*
	while (input.find(";") != std::string::npos) {
		int begin = input.find(";");
		int end = input.find("\n");
		if (end == std::string::npos)
			input = input.substr(0, begin);
		else
			input = input.substr(0, begin) + input.substr(end);
	}
	*/

	while (input.find(";") != std::string::npos) {
		while (input.substr(0, 1) == "\n")
			input.replace(0, 1, "");
		size_t begin = input.find(";");
		size_t end = input.find("\n");
		if (end < begin) {
			input.replace(end, 1, " ");
		}
		else {
			if (end == std::string::npos) {
				input.replace(begin, input.size() - 1, " ");
			}
			else {
				end = end + 1;
				input.replace(begin, end-begin, " ");
			}
		}
	}

	//std::cout << "*" << input << std::endl;

	//pads all parentheses with whitespace
	padParen(input);

	std::string word;
	std::list<std::string> token_list;
	std::istringstream iss(input, std::istringstream::in);

	//splits into individual tokens and adds to list
	while (iss >> word)
	{
		token_list.push_back(word);
	}

	return token_list;
}

//iterates through string and adds whitespace to parentheses
void Tokenizer::padParen(std::string& str) {
	int start_pos = 0;
	while ((start_pos = str.find("(", start_pos)) != std::string::npos) {
		str.replace(start_pos, 1, " ( ");
		start_pos += 3; 
	}
	start_pos = 0;
	while ((start_pos = str.find(")", start_pos)) != std::string::npos) {
		str.replace(start_pos, 1, " ) ");
		start_pos += 3;
	}
}