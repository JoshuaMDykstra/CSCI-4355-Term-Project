#include "Lexeme.h"

Lexeme::Lexeme(int typeID, std::string lexValue, int lineNum) {
	lexemeType = typeID;
	lexemeValue = lexValue;
	sourceLine = lineNum;
}

int Lexeme::getTypeID() {
	return lexemeType;
}

std::string Lexeme::getTypeStr() {
	switch (lexemeType) {
	case 1:
		return "RESERVED_WORD";
	case 2:
		return "OPERATOR";
	case 3:
		return "IDENTIFIER";
	case 4:
		return "NUMBER";
	}
}

std::string Lexeme::getValue() {
	return lexemeValue;
}

void Lexeme::setType(int typeID) {
	lexemeType = typeID;
}