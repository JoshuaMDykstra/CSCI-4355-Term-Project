#include "grammar.h"

grammar::grammar(std::deque<lexeme>* quePtr, lexeme* frontPtr) {
	lexemeList = quePtr;
	frontLexeme = frontPtr;

	if (not PROGRAM()) {
		grammarError();
	}
}

void grammar::grammarError() {
	std::cout << errorMessage << std::endl;
	exit(1);
}

//Rule 01: PROGRAM->program DECL_SEC begin STMT_SEC end; | program begin STMT_SEC end;
bool grammar::PROGRAM() {
	
	std::cout << "PROGRAM" << std::endl;

	if (frontLexeme->getValue() == "program") {
		lexemeList->pop_front();
	}
	else {
		errorMessage = "ERROR !! reserved word: program missing on line " + frontLexeme->getSourceLine() + '.';
		return false;
	}

	DECL_SEC();

	if (frontLexeme->getValue() == "begin") {
		lexemeList->pop_front();
	}
	else {
		errorMessage = "ERROR !! reserved word: begin missing on line " + frontLexeme->getSourceLine() + '.';
		return false;
	}

	if (not STMT_SEC()) {
		return false;
	}

	if (frontLexeme->getValue() == "end") {
		lexemeList->pop_front();
		if (not checkSemicolon()) {
			return false;
		}
	}
	else {
		errorMessage = "ERROR !! reserved word: end missing on line " + frontLexeme->getSourceLine() + '.';
		return false;
	}

	return true;
}

//Rule 02: DECL_SEC->DECL | DECL DECL_SEC
void grammar::DECL_SEC() {

	std::cout << "DECL_SEC" << std::endl;

	while (true) {
		if (not DECL()) {
			break;
		}
	}

	return;
}

//Rule 03 : DECL->ID_LIST : TYPE;
bool grammar::DECL() {

	std::cout << "DECL" << std::endl;

	if (ID_LIST() == false) {
		return false;
	}
	
	if (frontLexeme->getValue() == ":") {
		std::cout << ":" << std::endl;
		lexemeList->pop_front();
	}
	else {
		errorMessage = "ERROR !! missing colon on line " + frontLexeme->getSourceLine() + '.';
		return false;
	} 

	if (not TYPE()) {
		return false;
	}

	if (not checkSemicolon()) {
		return false;
	}

	return true;
}

//Rule 04: ID_LIST->ID | ID, ID_LISTRule 06 : STMT_SEC à STMT | STMT STMT_SEC
bool grammar::ID_LIST() {

	std::cout << "ID_LIST" << std::endl;

	return false;
}

//Rule 05 : ID(_ | a | b | … | z | A | … | Z) (_ | a | b | … | z | A | … | Z | 0 | 1 | … | 9) *
bool grammar::ID() {

	std::cout << "ID" << std::endl;

	return false;
}

//Rule 06: STMT_SEC->STMT | STMT STMT_SEC
bool grammar::STMT_SEC() {

	std::cout << "STMT_SEC" << std::endl;

	return false;
}

//Rule 07 : STMT->ASSIGN | IFSTMT | WHILESTMT | INPUT | OUTPUT
bool grammar::STMT() {

	std::cout << "STMT" << std::endl;

	return false;
}

//Rule 08 : ASSIGN->ID : = EXPR;
bool grammar::ASSIGN() {

	std::cout << "ASSIGN" << std::endl;

	return false;
}

//Rule 09: IFSTMT -> if COMP then STMT_SEC end if; | if COMP then STMT_SEC else STMT_SEC end if;
bool grammar::IFSTMT() {

	std::cout << "IFSTMT" << std::endl;

	return false;
}

//Rule 10: WHILESTMT -> while COMP loop STMT_SEC end loop;
bool grammar::WHILESTMT() {

	std::cout << "WHILESTMT" << std::endl;

	return false;
}

//Rule 11: INPUT->input ID_LIST;
bool grammar::INPUT() {

	std::cout << "INPUT" << std::endl;

	return false;
}

//Rule 12: OUTPUT->output ID_LIST; | output NUM;
bool grammar::OUTPUT() {

	std::cout << "OUTPUT" << std::endl;

	return false;
}

//Rule 13: EXPR->FACTOR | FACTOR + EXPR | FACTOR - EXPR
bool grammar::EXPR() {

	std::cout << "EXPR" << std::endl;

	return false;
}

//Rule 14 : FACTOR->OPERAND | OPERAND * FACTOR | OPERAND / FACTOR
bool grammar::FACTOR() {

	std::cout << "FACTOR" << std::endl;

	return false;
}

//Rule 15 : OPERAND->NUM | ID | (EXPR)
bool grammar::OPERAND() {

	std::cout << "OPERAND" << std::endl;

	return false;
}

//*Rule 16 : NUM -> (0 | 1 | ... | 9) + [.(0 | 1 | … | 9) + ]
bool grammar::NUM() {

	std::cout << "NUM" << std::endl;

	return false;
}

//Rule 17 : COMP -> (OPERAND = OPERAND) | (OPERAND <> OPERAND) | (OPERAND > OPERAND) | (OPERAND < OPERAND)
bool grammar::COMP() {

	std::cout << "COMP" << std::endl;

	return false;
}

//Rule 18 : TYPE -> int | float | double
bool grammar::TYPE() {

	std::cout << "TYPE" << std::endl;

	const std::string validTypes[3] = { "int", "float", "double" };

	return false;
}

bool grammar::checkSemicolon() {
	if (frontLexeme->getValue() == ";") {
		lexemeList->pop_front();
		return true;
	}
	else {
		errorMessage = "ERROR !! semicolon missing on line " + frontLexeme->getSourceLine() + '.';
		return false;
	}
}