#include <iostream>
#include <string>
#include "../tokenizer/chunks.h"
#include <regex>
#include "test.h"
#include "../tokenizer/tokenizer.h"
void test() {
	std::string str = """<html           idonthaveval  class     =   'test' id ='tag'>This is test  </br >  <   label>test</label>Do u understand?</html>""";
	tokenize(str);
	return;
};