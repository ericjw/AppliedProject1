#include "tokenize.hpp"

//tokenizes input given as a string
std::list<std::string>& tokenize(std::string input) {
	//scrub comments
	input = input.substr(0, input.find(";", 0));

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
void padParen(std::string& str) {
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