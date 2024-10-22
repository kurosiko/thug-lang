/*
#include <map>
#include <string>
#include <vector>
#include "../Types/types.h"
#include <string>
struct AST
{

	std::string tag_name;
	std::vector<std::string> cls;
	std::vector<std::string> id;
	std::vector<AST> child;
};
struct AST_All
{
	struct AST ast;
	//std::vector<std::vector<AST*>> cls;
	//std::vector<std::vector<AST*>> id;
	
};
struct AST parser(const std::vector<std::pair<TokenizeKey, std::string>>& tokenized_keys) {
	bool in_tag = false;
	struct AST main;
	struct AST ast_cache;
	for (auto&& key : tokenized_keys) {
		switch (key.first){
			struct AST
			{
				std::string tag_name;
				std::vector<std::string> cls;
				std::vector<std::string> id;
				std::vector<AST> child;
			};
		case TAG_OPEN:
			main.child.push_back(ast_cache);
			break;
		case TAG_NAME:
			ast_cache.tag_name = key.second;
			break;
		case ATTR_NAME:
			break;
		default:
			break;
		}
	};
};
*/