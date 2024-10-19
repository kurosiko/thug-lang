#include <iostream>
#include <string>
#include "../tokenizer/chunks.h"
#include <regex>
#include "test.h"
#include "../tokenizer/tokenizer.h"
void test() {
	std::string str = "<TAG novalcls cls=\"test test2\" nvalcls2 >This is inner text</TAG>";
	Tokenizer tokenizer;
	tokenizer.tokenize(str);
	return;
};