//lexeme.h
 
#pragma once

//library includes
#include <string>

//project includes
#include "utils.h"

class lexeme
{
private:
//attributes
	lexemeType lexType;
	std::string lexemeValue;
	int sourceLine;

public:
//constructor
	lexeme(std::string lexValue, int lineNum, lexemeType typeInput);

//getters
	int getTypeID() { return lexType; }
	std::string getTypeStr();
	std::string getValue() { return lexemeValue; }
	int getSourceLine() { return sourceLine; }

//setters
	void setType(lexemeType typeID) { lexType = typeID; }
};