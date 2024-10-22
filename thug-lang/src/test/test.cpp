#include <iostream>
#include <string>
#include "../tokenizer/chunks.h"
#include <regex>
#include "test.h"
#include "../tokenizer/tokenizer.h"
void test() {
	std::string str = "out of tag(error)#<TAG novalcls cls = \"  test test2\" nvalcls2><TAG2 novalcls cls = \"  test test2\" nvalcls2>InnerText</TAG2></TAG>";
	Tokenizer tokenizer;
	tokenizer.tokenize(str);
	return;
};