enum TokenizeKey {
	TAG_OPEN,
	TAG_CLOSE,
	TAG_SELF,
	TAG_NAME,
	ATTR_NAME,
	ATTR_VAL,
	SLASH,
	EQUAL,
	DOUBLE_QUOT,
	SINGLE_QUOT,
	INNER_ELEMENT,
};
enum State {
	Ready,
	TagName,
	InnerAttrName,
	InnerAttrVal,
	InnerAttrVal_main
};
enum Quot {
	Single,
	Double
};