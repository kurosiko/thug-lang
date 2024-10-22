#ifndef token_h
#define token_h
#include <vector>
#include <string>
#include "../Types/types.h"
#endif
class Tokenizer {
private:
	std::vector<std::pair<TokenizeKey, std::string>> tokenized;
	void push_mem(TokenizeKey key, std::string val);
	void ReadyState(std::string::iterator& it, bool& init, std::string::iterator& cache_it, State& state);
	void TagNameState(std::string::iterator& it, bool& init, std::string::iterator& cache_it, State& state, bool& waitNspace);
	void AttrNameState(std::string::iterator& it, bool& init, std::string::iterator& cache_it, State& state, bool& waitNspace);
	void AttrValState(std::string::iterator& it, Quot& quot, State& state,bool& waitNspace);
	void AttrValMainState(std::string::iterator& it, bool& init, std::string::iterator& cache_it, Quot& quot, State& state, bool& waitNspace);
public:
	std::vector<std::pair<TokenizeKey, std::string>> tokenize(std::string& input);
};