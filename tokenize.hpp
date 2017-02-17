#include <list>
#include <string>
#include <iostream>
#include <sstream>

//accepts a string of arguments and returns a list of tokens
std::list<std::string> tokenize(std::string input);
//helper method to replace parenthese
void padParen(std::string& str);