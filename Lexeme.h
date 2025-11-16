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
	lexeme(std::string lexValue, int lineNum);

//getters
	int getTypeID();
	std::string getTypeStr();
	std::string getValue();
	int getSourceLine();

//setters
	void setType(lexemeType typeID);
};