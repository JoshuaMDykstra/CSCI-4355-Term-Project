#pragma once

#include <string>

//lexeme types
#define UNKNOWN 0
#define RESERVED_WORD 1
#define OPERATOR 2
#define IDENTIFIER 3
#define NUMBER 4

class Lexeme
{
private:
	int lexemeType;
	std::string lexemeValue;
	int sourceLine;

public:
//constructor
	Lexeme(int typeID, std::string lexValue, int lineNum);

//getters
	int getTypeID();
	std::string getTypeStr();
	std::string getValue();

//setters
	void setType(int typeID);
};

