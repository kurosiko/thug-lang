#include <vector>
#include <string>
#include "string_util.h"

std::vector<std::string>split(const std::string& str,const char del) {
	int index = 0;
	int index_last = str.find_first_of(del,0);
	std::vector<std::string> result;
	while (index < str.size()) {
		std::string subStr = str.substr(index, index_last - index);
		result.push_back(subStr);
		index = index_last + 1;
		index_last = str.find_first_of(del, index);
		if (index_last == std::string::npos) {
			index_last = str.size();
		};

	}
	return result;
};

std::string iterator_substr(std::string::iterator& iterator_begin, std::string::iterator& iterator_end) {
	std::string result;
	for (std::string::iterator iterator_cur = iterator_begin; iterator_cur != iterator_end; ++iterator_cur) {
		result.push_back(*iterator_cur);
	};
	return result;
};