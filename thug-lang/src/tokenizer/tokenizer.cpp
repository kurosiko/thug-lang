#include <vector>
#include <string>
#include <iostream>
#include <regex>
#include "tokenizer.h"
#include "chunks.h"
#include "../utils/string_util.h"


std::vector<std::string> tokenize(std::string& input) {
	int start_blank = 0;
	int end_blank = 0;
	int tag_name_end = 0;
	std::string::iterator tag_name_begin;
	std::string tag;
	std::string inner;
	int state = 0;
	/*
	0:default
	1:tag_name
	2;attribute
	*/
	std::vector<std::string> sprited;
	for (std::string::iterator current_str = input.begin(); current_str != input.end();++current_str) {
		if (state == 0) {
			if (*current_str != '<') {
				continue;
			};
			/*
			switch (*current_str) {
			case ' ':
				continue;
			case '	':
				continue;
			default:
				break;
			};
			*/
		};
		if (state == 1) {
			switch (*current_str){
			case ' ':
			case '>':
				std::cout << iterator_substr(tag_name_begin, current_str) << std::endl;
				state = 2;
			default:
				break;
			};
			
		};
		if (state == 2) {

		}
		if (*current_str == '<') {
			state = 1;
			tag_name_begin = current_str + 1;
		};
		if (*current_str == '>') {
			state = 0;
		};
		//std::cout << state <<':'<< *current_str << std::endl;
	};
	for (const auto& str : sprited) {
		std::cout << str << '\n';
	};
	return sprited;
};