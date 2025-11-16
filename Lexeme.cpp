#include "lexeme.h"

//constructor
lexeme::lexeme(std::string lexValue, int lineNum) {
	lexemeValue = lexValue;
	sourceLine = lineNum + 1;
    lexType = ERROR;

    //check for reserved words
    if (isReservedWord(lexValue)) {
        lexType = RESERVED_WORD;
    }
    //check for identifiers
    else if (isalpha(lexValue[0]) || lexValue[0] == '_') {
        lexType = IDENTIFIER;
    }
    //check for operators
    else if (isOperator(lexValue[0])) {
        lexType = OPERATOR;
    }
    //check for number literals
    else if (isdigit(lexValue[0])) {

        //check all following characters are numbers
        for (int i = 0; i < lexValue.size(); i++) {
            if (not std::isdigit(lexValue[i])) {
                lexType = ERROR;
            }
            else if (lexValue.size() == i + 1) {
                lexType = NUMBER;
            }
        }
    }
}

//getters
int lexeme::getTypeID() {
	return lexType;
}

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

std::string lexeme::getValue() {
	return lexemeValue;
}

int lexeme::getSourceLine() {
    return sourceLine;
}

//setters
void lexeme::setType(lexemeType typeID) {
	lexType = typeID;
}