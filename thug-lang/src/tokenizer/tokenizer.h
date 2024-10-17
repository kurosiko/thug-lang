#ifndef token_h
#define token_h
#include <vector>
#include <string>
#include "../Types/types.h"
#endif
class Tokenizer {
private:
	std::vector<std::pair<TokenizeKey, std::string>> tokenized;
	void push_mem(TokenizeKey key,std::string val);
public:
	std::vector<std::pair<TokenizeKey, std::string>> tokenize(std::string& input);
};