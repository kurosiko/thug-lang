#include <iostream>
#include <string>
#include "../tokenizer/chunks.h"
#include <regex>
#include "test.h"
#include "../tokenizer/tokenizer.h"
void test() {
	std::string str = """<TAG class=\"  CLS1 CLS2 CLS3\"/>""";
	Tokenizer tokenizer;
	tokenizer.tokenize(str);
	return;
};