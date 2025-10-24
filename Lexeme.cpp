#include "Lexeme.h"

Lexeme::Lexeme(std::string lexValue, int lineNum) {
	lexemeValue = lexValue;
	sourceLine = lineNum;
    lexemeType = ERROR;

    //check for reserved words
    if (isReservedWord(lexValue)) {
        lexemeType = RESERVED_WORD;
    }
    //check for identifiers
    else if (isalpha(lexValue[0]) || lexValue[0] == '_') {
        lexemeType = IDENTIFIER;
    }
    //check for operators
    else if (isOperator(lexValue[0])) {
        lexemeType = OPERATOR;
    }
    //check for number literals
    else if (isdigit(lexValue[0]))
    for (int i = 0; i < lexValue.size(); i++) {
        if (not std::isdigit(lexValue[i])) {
            lexemeType = ERROR;
        }
        else if (lexValue.size() == i + 1) {
            lexemeType = NUMBER;
        }
    }
}

int Lexeme::getTypeID() {
	return lexemeType;
}

std::string Lexeme::getTypeStr() {
	switch (lexemeType) {
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

std::string Lexeme::getValue() {
	return lexemeValue;
}

void Lexeme::setType(int typeID) {
	lexemeType = typeID;
}