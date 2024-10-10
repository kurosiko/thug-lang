#include <regex>
#include <iostream>
void chunker(const std::regex& regex,const std::string& str) {
	std::smatch match;
	std::regex_match(str,match, regex);
	std::cout << match.length() << std::endl;
};