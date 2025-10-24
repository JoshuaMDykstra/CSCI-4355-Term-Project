#pragma once

#include <string>

//lexeme types
#define RESERVED_WORD 1
#define OPERATOR 2
#define IDENTIFIER 3
#define NUMBER 4

class Lexeme
{
private:
	int lexemeType;
	std::string lexemeValue;

public:
//constructor
	Lexeme(int typeID, std::string lexValue);
//getters
	int getTypeID();
	std::string getTypeStr();
	std::string getValue();
};

