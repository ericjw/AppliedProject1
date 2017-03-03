#include "tokenize.hpp"

//tokenizes input given as a string
std::list<std::string> Tokenizer::tokenize(std::string input) {
	//scrub comments
	while (input.find(";") != std::string::npos) {
		int begin = input.find(";");
		int end = input.find("\n");
		if (end == std::string::npos)
			input = input.substr(0, begin);
		else
			input = input.substr(0, begin) + input.substr(end);
	}

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