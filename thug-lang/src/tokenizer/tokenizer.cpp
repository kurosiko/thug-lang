#ifndef lib
	#define lib
	#include <vector>
	#include <string>
	#include <iostream>
	#include <regex>
	#include "tokenizer.h"
	#include "chunks.h"
	#include "../utils/string_util.h"
#endif

std::vector<std::string> tokenize(std::string& input) {
	int start_blank = 0;
	int end_blank = 0;
	int tag_name_end = 0;
	enum State {
		Ready,
		TagName,
		InnerAttrName,
		InnerAttrVal,
	};
	enum Quontation {
		Double,
		Single
	};
	Quontation quot;
	State state = Ready;
	bool waitNspace = false;
	bool safeNspace = false;
	std::string::iterator begin_cache;
	std::string::iterator end_cache;
	std::string tag;
	std::string inner;
	bool cached = false;
	std::vector<std::string> sprited;
	for (std::string::iterator current_str = input.begin(); current_str != input.end();++current_str) {
		if (waitNspace && *current_str == ' ') continue;
		waitNspace = false;
		switch (state) {
		case Ready:
			if (*current_str == '<') {
				state = TagName;
				begin_cache = current_str + 1;
			};
			break;
		case TagName:
			if (*current_str == '>' || *current_str == ' ') {
				std::cout << iterator_substr(begin_cache, current_str) << std::endl;
				state = (*current_str == '>') ? Ready : InnerAttrName;
				waitNspace = true;
			};
			break;
		case InnerAttrName:
			if (!cached) {
				begin_cache = current_str;
				cached = true;
			};
			if (*current_str == '=' || *current_str == '>' || *current_str == ' ') {
				std::cout << iterator_substr(begin_cache, current_str) << std::endl;
				state = (*current_str == '>') ? Ready : InnerAttrName;
				if (*current_str == '=') state = InnerAttrVal;
				waitNspace = true;
				cached = false;
			};
			break;
		case InnerAttrVal:
			if (!cached) {
				begin_cache = current_str;
				cached = true;
			};
			if (*current_str == '>' || *current_str == ' ') {
				std::cout << iterator_substr(begin_cache, current_str) << std::endl;
				state = (*current_str == '>') ? Ready :InnerAttrName;
				waitNspace = true;
				cached = false;
			};
			break;
		};
		std::cout << state << ':' << *current_str << std::endl;
	};
	return sprited;
};