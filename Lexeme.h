#pragma once

#include <string>

#include "utils.h"

//lexeme types
#define UNKNOWN 0
#define ERROR 1
#define RESERVED_WORD 2
#define OPERATOR 3
#define IDENTIFIER 4
#define NUMBER 5

class Lexeme
{
private:
	int lexemeType;
	std::string lexemeValue;
	int sourceLine;

public:
//constructor
	Lexeme(std::string lexValue, int lineNum);

//getters
	int getTypeID();
	std::string getTypeStr();
	std::string getValue();

//setters
	void setType(int typeID);
};