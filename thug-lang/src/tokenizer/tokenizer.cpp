#ifndef token
#define token
#include <iostream>
#include "./tokenizer.h"
#endif

std::vector<std::pair<TokenizeKey, std::string>> Tokenizer::tokenize(std::string& input) {
	State state = Ready;
	bool waitNspace = true;
	std::string::iterator cache_it;
	bool init = false;
	Quot quot;
	for (std::string::iterator it = input.begin(); it != input.end(); ++it) {
		if (waitNspace && *it == ' ') { continue; };
		waitNspace = false;
		switch (state)
		{
		case Ready:
			ReadyState(it, init, cache_it, state);
			break;
		case TagName:
			TagNameState(it, init, cache_it, state,waitNspace);
			break;
		case InnerAttrName:
			AttrNameState(it, init, cache_it, state, waitNspace);
			break;
		case InnerAttrVal:
			AttrValState(it,quot,state,waitNspace);
			break;
		case InnerAttrValMain:
			AttrValMainState(it,init,cache_it,quot,state,waitNspace);
			break;
		}
	};
	for (auto&& el : tokenized) std::cout << "Tokenize:" << el.first << ':' << el.second << std::endl;
	return tokenized;
};
void Tokenizer::push_mem(TokenizeKey key, std::string val) { 
	tokenized.push_back(std::make_pair(key, val));
}
void Tokenizer::ReadyState(std::string::iterator& it, bool& init, std::string::iterator& cache_it, State& state)
{
	if (*it == '<') {
		if (init) {
			init = false;
			push_mem(INNER_TEXT, std::string(cache_it, it));
		};
		push_mem(TAG_OPEN, "<");
		cache_it = it + 1;
		state = TagName;
	}
	else if (!init) {
		init = true;
		cache_it = it;
	};
}
void Tokenizer::TagNameState(std::string::iterator& it, bool& init, std::string::iterator& cache_it, State& state,bool& waitNspace)
{
	if (!init) {
		init = true;
		if (*it == '/') {
			push_mem(SLASH, std::string("/"));
			cache_it = it + 1;
			return;
		};
	};
	if (*it == '>' || *it == ' ' || *it == '/') {
		if (*it == '>') {
			push_mem(TAG_NAME, std::string(cache_it, it));
			push_mem(TAG_CLOSE, ">");
			state = Ready;
		}
		else if (*it == '/' && *(it + 1) == '>') {
			push_mem(TAG_NAME, std::string(cache_it, it));
			push_mem(TAG_SELF, "/");
			push_mem(TAG_CLOSE, ">");
			state = Ready;
		}
		else if (*it == ' ') {
			push_mem(TAG_NAME, std::string(cache_it, it));
			state = InnerAttrName;
		};
		waitNspace = true;
		init = false;
	};

}
void Tokenizer::AttrNameState(std::string::iterator& it, bool& init, std::string::iterator& cache_it, State& state,bool& waitNspace)
{
	if (!init) {
		init = true;
		cache_it = it;
	};
	if (*it == '=' || *it == '>' || *it == ' ' || *it == '/') {
		if (*it == '=') {
			if (cache_it != it) {
				push_mem(ATTR_NAME, std::string(cache_it, it));
			};
			push_mem(EQUAL, "=");
			state = InnerAttrVal;
		}
		else if (*it == ' ') {
			push_mem(ATTR_NAME, std::string(cache_it, it));
		}
		else if (*it == '/' && *(it + 1) == '>') {
			if (cache_it != it) {
				push_mem(ATTR_NAME, std::string(cache_it, it));
			};
			push_mem(TAG_SELF, "/");
			push_mem(TAG_CLOSE,">");
			state = Ready;
		}
		else if (*it == '>') {
			if (cache_it != it) {
				push_mem(ATTR_NAME, std::string(cache_it, it));
			};
			push_mem(TAG_CLOSE,">");
			state = Ready;
		};
		waitNspace = true;
		init = false;
	};
}
void Tokenizer::AttrValState(std::string::iterator& it,Quot& quot, State& state,bool& waitNspace)
{
	if (*it == '\'' || *it == '"') {
		quot = (*it == '"') ? Double : Single;
		push_mem(quot == Single ? SINGLE_QUOT : DOUBLE_QUOT, std::string(1, *it));
		state = InnerAttrValMain;		
		waitNspace = true;
		return;
	}
	else {
		throw std::runtime_error("InnerAttVal must be started by single or double quot.");
	};
}
void Tokenizer::AttrValMainState(std::string::iterator& it, bool& init, std::string::iterator& cache_it,Quot& quot ,State& state,bool& waitNspace)
{
	if (!init) {
		init = true;
		cache_it = it;
	};
	if ((*it == '\'' && quot == Single) || (*it == '"' && quot == Double)) {
		if (*(it - 1) != ' ') {
			push_mem(ATTR_VAL, std::string(cache_it, it));
		};
		push_mem(quot == Single ? SINGLE_QUOT : DOUBLE_QUOT, std::string(1,*it));
		state = InnerAttrName;
		waitNspace = true;
		init = false;
		cache_it = it + 1;
	};
	if (*it == ' ') {
		push_mem(ATTR_VAL, std::string(cache_it, it));
		init = false;
		waitNspace = true;
	};
}
;