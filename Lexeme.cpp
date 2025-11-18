//lexeme.cpp

#include "lexeme.h"

//constructor
lexeme::lexeme(std::string lexValue, int lineNum, lexemeType typeInput) {
	lexemeValue = lexValue;
	sourceLine = lineNum;
    lexType = typeInput;
}

//getters
std::string lexeme::getTypeStr() {

    //switch to decode type id
	switch (lexType) {
	case 2:
		return "RESERVED_WORD";
	case 3:
		return "OPERATOR";
	case 4:
		return "IDENTIFIER";
	case 5:
		return "NUMBER";
    default:
        return "getTypeStr Error";
	}
}