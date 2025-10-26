#pragma once

#include <iostream>
#include <deque>

#include "lexeme.h"

class grammar {

private:
	std::deque<lexeme>* lexemeList;
	lexeme* frontLexeme;
	std::string errorMessage;

public:
	grammar(std::deque<lexeme>* quePtr, lexeme* frontPtr);
	void grammarError();
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
	bool checkSemicolon();
};
