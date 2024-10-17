#ifndef token
#define token
#include <iostream>
#include "./tokenizer.h"
#endif

std::vector<std::pair<TokenizeKey, std::string>> Tokenizer::tokenize(std::string& input) {
	State state = Ready;
	bool waitNspace = false;
	bool waitspace = false;
	std::string::iterator cache_it;
	bool init = false;
	Quot quot;
	for (std::string::iterator it = input.begin(); it != input.end(); ++it) {
		if (waitNspace && *it == ' ') continue;
		switch (state)
		{
		case Ready:
			if (*it == '<') {
				push_mem(TAG_OPEN, std::string("<"));
				cache_it = it + 1;
				state = TagName;
				
			};
			break;
		case TagName:
			if (!init) {
				init = true;
				if (*it == '/') {
					push_mem(SLASH, std::string("/"));
					cache_it = it + 1;
					continue;
				};
			};
			if (*it == '>' || *it == ' ' || *it == '/') {
				if (*it == '>') {
					push_mem(TAG_NAME, std::string(cache_it, it-1));
					push_mem(TAG_CLOSE, std::string(">"));
					state = Ready;
				}
				else if (*it == '/' && *(it+1) == '>') {
					push_mem(TAG_SELF, std::string("/"));
				}
				else if (*it == ' ') {
					push_mem(TAG_NAME, std::string(cache_it, it));
					state = InnerAttrName;
				};
				waitNspace = true;
				init = false;
			};
			
			break;
		case InnerAttrName:
			if (!init) {
				init = true;
				cache_it = it;
			};
			if (*it == '=' || *it == '>' || *it == ' ' || *it == '/') {
				if (*it == '=') {
					push_mem(ATTR_NAME, std::string(cache_it, it-1));
					push_mem(EQUAL, std::string("="));
					state = InnerAttrVal;
				}else if (*it == ' ') {
					push_mem(ATTR_NAME, std::string(cache_it, it));
				}else if (*it == '/' && *(it+1) == '>') {
					push_mem(TAG_SELF, std::string("/"));
				}else if (*it == '>') {
					push_mem(TAG_NAME, std::string(cache_it, it - 1));
					push_mem(TAG_CLOSE, std::string(">"));
					state = Ready;
				};
				waitNspace = true;
				init = false;
			};
			break;
		case InnerAttrVal:
			if (!init) {
				init = true;
				cache_it = it;
				waitNspace = true;
				if (*it == '\'') {
					push_mem(SINGLE_QUOT, std::string("'"));
					quot = Single;
				}else if (*it == '"') { 
					push_mem(DOUBLE_QUOT, std::string("\""));// doesn't work
					quot = Double;
				}
				else throw std::runtime_error("InnerAttVal must be started by single or double quot.");
				cache_it = it;
			};
			if ((*it == '\'' && quot == Single && *(it - 1) != '\\') || (*it == '"' && quot == Double && *(it - 1) != '\\')) {
				state = InnerAttrVal;
				waitNspace = true;
				init = false;
			}
			else if(*it == ' ' ){
				waitNspace = true;
			};
			break;
		default:
			break;
		}
		std::cout << *it << ':' << state << std::endl;
	};
	for (auto&& el : tokenized) std::cout << "Tokenize:" << el.first << ':' << el.second << std::endl;
	return tokenized;
};
void Tokenizer::push_mem(TokenizeKey key, std::string val) { 
	tokenized.push_back(std::make_pair(key, val));
};