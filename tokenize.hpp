#ifndef _TOKENIZE_H_
#define _TOKENIZE_H_

#include <list>
#include <string>
#include <iostream>
#include <sstream>


class Tokenizer {
	//helper method to replace parentheses
	void padParen(std::string& str);
public:
	//accepts a string of arguments and returns a list of tokens
	std::list<std::string> tokenize(std::string input);

};

#endif