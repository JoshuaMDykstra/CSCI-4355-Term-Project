#pragma once

//library includes
#include <string>

//debug setting
const bool debugFlag = true;

enum lexemeType {
	UNKNOWN,
	ERROR,
	RESERVED_WORD,
	OPERATOR,
	IDENTIFIER,
	NUMBER
};

//prototypes
bool isOperator(char target);
bool isReservedWord(std::string input);