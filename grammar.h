#pragma once

#include <iostream>
#include <deque>
#include <vector>

#include "lexeme.h"
#include "utils.h"

class grammar {

public:
	//constructor
	grammar(std::deque<lexeme>* quePtr);

private:

	//attributes
	std::deque<lexeme>* lexemeList;
	std::string errorMessage;
	std::vector<std::string> tokens;

	//debugging, error, and output functions
	void grammarError();
	void debugMsg(std::string msg);
	void debugLex(lexeme inputLex);
	void printTokens();

	//grammar rule functions
	bool PROGRAM();
	void DECL_SEC();
	bool DECL();
	bool ID_LIST();
	bool ID();
	bool STMT_SEC();
	bool STMT();
	bool ASSIGN();
	bool IFSTMT();
	bool WHILESTMT();
	bool INPUT();
	bool OUTPUT();
	bool EXPR();
	bool FACTOR();
	bool OPERAND();
	bool NUM();
	bool COMP();
	bool TYPE();

	//convenience function
	bool checkSemicolon();
};
