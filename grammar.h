//grammar.h

#pragma once

#include <iostream>
#include <deque>
#include <vector>

#include "lexeme.h"

class grammar {

public:
	//constructor
	grammar(std::deque<lexeme>* quePtr);

private:

	//attributes
	std::deque<lexeme>* lexemeList;
	std::string errorMessage = "UNKNOWN GRAMMAR ERROR";
	std::vector<std::string> tokens;
	bool declerationSectionFlag = true;
	std::vector<std::string> declaredIdentifiers;

	//debugging, error, and output functions
	void grammarError();
	void printLexemes();
	void printTokens();

	//grammar rule functions
	bool PROGRAM();
	bool DECL_SEC();
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
	bool checkLexeme(std::string word);
	bool identifierDeclared();
};