#include "grammar.h"

#define NEXTLEX debugLex(lexemeList->front()); lexemeList->pop_front();

grammar::grammar(std::deque<lexeme>* quePtr) {
	lexemeList = quePtr;
	errorMessage = "UNKNOWN GRAMMAR ERROR";

	if (not PROGRAM()) {

		printTokens();
		if (debugFlag) {
			std::cout << "##### GRAMMAR ERROR #####" << std::endl << std::endl;
		}

		grammarError();
	}
	else {

		printTokens();
	}
}

void grammar::grammarError() {

	std::cout << errorMessage << std::endl;
	exit(1);
	
}

void grammar::debugMsg(std::string msg) {
	if (debugFlag) {
		std::cout << "DEBUG: " << msg << std::endl;
	}
}

void grammar::debugLex(lexeme inputLex) {
	if (debugFlag) {
		std::cout << "DEBUG: " << inputLex.getTypeStr() << " \"" << inputLex.getValue() << "\" Line:" << inputLex.getSourceLine() << std::endl;
	}
}

void grammar::printTokens() {

	if (debugFlag) {
		std::cout << "##### PRINTING TOKENS #####" << std::endl << std::endl;

	}

	for (int i = 0; i < tokens.size(); i++)
		std::cout << tokens[i] << std::endl;
}

//Rule 01: PROGRAM->program DECL_SEC begin STMT_SEC end; | program begin STMT_SEC end;
bool grammar::PROGRAM() {
	
	tokens.push_back("PROGRAM");

	if (lexemeList->front().getValue() == "program") {
		debugLex(lexemeList->front());
		lexemeList->pop_front();
	}
	else {
		errorMessage = "ERROR !! reserved word: program missing on line " + std::to_string(lexemeList->front().getSourceLine()) + '.';
		return false;
	}

	DECL_SEC();

	if (lexemeList->front().getValue() == "begin") {
		debugLex(lexemeList->front());
		lexemeList->pop_front();
	}
	else {
		//TODO FIX THIS
		errorMessage = "ERROR !! reserved word: begin missing on line " + std::to_string(lexemeList->front().getSourceLine()) + '.';
		return false;
	}

	if (not STMT_SEC()) {
		return false;
	}

	if (lexemeList->front().getValue() == "end") {
		debugLex(lexemeList->front());
		lexemeList->pop_front();
		if (not checkSemicolon()) {
			return false;
		}
	}
	else {
		errorMessage = "ERROR !! reserved word: end missing on line " + std::to_string(lexemeList->front().getSourceLine()) + '.';
		return false;
	}

	return true;
}

//Rule 02: DECL_SEC->DECL | DECL DECL_SEC
void grammar::DECL_SEC() {

	tokens.push_back("DECL_SEC");

	while (true) {
		if (not DECL()) {
			break;
		}
	}

	return;
}

//Rule 03 : DECL->ID_LIST : TYPE;
bool grammar::DECL() {

	tokens.push_back("DECL");

	if (ID_LIST() == false) {
		tokens.pop_back();
		return false;
	}
	
	if (lexemeList->front().getValue() == ":") {
		debugLex(lexemeList->front());
		lexemeList->pop_front();
	}
	else {
		errorMessage = "ERROR !! missing colon on line " + std::to_string(lexemeList->front().getSourceLine()) + '.';
		tokens.pop_back();
		return false;
	} 

	if (not TYPE()) {
		tokens.pop_back();
		return false;
	}

	if (not checkSemicolon()) {
		return false;
	}

	return true;
}

//Rule 04: ID_LIST->ID | ID, ID_LIST
bool grammar::ID_LIST() {

	tokens.push_back("ID_LIST");

	if (ID()) {

		if (lexemeList->front().getValue() == ",") {

			debugLex(lexemeList->front());
			lexemeList->pop_front();

			ID_LIST();
		}
		return true;
	}
	else {
		errorMessage = "ERROR !! impropper id list on line " + std::to_string(lexemeList->front().getSourceLine()) + '.';
		tokens.pop_back();
		return false;
	}
}

//Rule 05 : ID(_ | a | b | … | z | A | … | Z) (_ | a | b | … | z | A | … | Z | 0 | 1 | … | 9) *
bool grammar::ID() {

	if (debugFlag) {
		tokens.push_back("DEBUG_ID");
	}

	if (lexemeList->front().getTypeID() == IDENTIFIER) {
		debugLex(lexemeList->front());
		lexemeList->pop_front();
	}
	else {
		errorMessage = "ERROR !! impropper identifier on line " + std::to_string(lexemeList->front().getSourceLine()) + '.';
		return false;
	}

	return true;
}

//Rule 06: STMT_SEC->STMT | STMT STMT_SEC
bool grammar::STMT_SEC() {

	tokens.push_back("STMT_SEC");

	if (STMT()) {

		STMT_SEC();
		return true;
	}
	else {
		tokens.pop_back();
		errorMessage = "ERROR !! impropper statement section on line " + std::to_string(lexemeList->front().getSourceLine()) + '.';
		return false;
	}
}

//Rule 07 : STMT->ASSIGN | IFSTMT | WHILESTMT | INPUT | OUTPUT
bool grammar::STMT() {

	tokens.push_back("STMT");

	if (ASSIGN() || IFSTMT() || WHILESTMT() || INPUT() || OUTPUT()) {
		return true;
	}
	else {
		tokens.pop_back();
		return false;
	}
}

//Rule 08 : ASSIGN->ID := EXPR;
bool grammar::ASSIGN() {

	tokens.push_back("ASSIGN");

	if (ID()) {
		if (lexemeList->front().getValue() == ":=") {

			debugLex(lexemeList->front());
			lexemeList->pop_front();

			if (EXPR()) {
				if (checkSemicolon()) {
					return true;
				}
				else {
					tokens.pop_back();
					return false;
				}
			}
		}
	}

	tokens.pop_back();
	return false;
}

//Rule 09: IFSTMT -> if COMP then STMT_SEC end if; | if COMP then STMT_SEC else STMT_SEC end if;
bool grammar::IFSTMT() {

	//TODO
	tokens.push_back("IFSTMT");
	tokens.pop_back();

	return false;
}

//Rule 10: WHILESTMT -> while COMP loop STMT_SEC end loop;
bool grammar::WHILESTMT() {

	//TODO
	tokens.push_back("WHILESTMT");
	tokens.pop_back();

	return false;
}

//Rule 11: INPUT->input ID_LIST;
bool grammar::INPUT() {

	tokens.push_back("INPUT");

	if (lexemeList->front().getValue() == "input") {
		lexemeList->pop_front();
		if (ID_LIST()) {
			if (checkSemicolon()) {
				return true;
			}
			else {
				tokens.pop_back();
				return false;
			}
		}
		else {
			tokens.pop_back();
			return false;
		}
	}
	else {
		tokens.pop_back();
		return false;
	}
}

//Rule 12: OUTPUT->output ID_LIST; | output NUM;
bool grammar::OUTPUT() {

	tokens.push_back("OUTPUT");

	if (lexemeList->front().getValue() == "output") {
		lexemeList->pop_front();
		if (ID_LIST()) {
			if (checkSemicolon()) {
				return true;
			}
			else {
				tokens.pop_back();
				return false;
			}
		}
		else if (NUM()) {
			if (checkSemicolon()) {
				return true;
			}
			else {
				tokens.pop_back();
				return false;
			}
		} 
		else {
			tokens.pop_back();
			return false;
		}
	}
	else {
		tokens.pop_back();
		return false;
	}
}

//Rule 13: EXPR->FACTOR | FACTOR + EXPR | FACTOR - EXPR
bool grammar::EXPR() {

	tokens.push_back("EXPR");

	if (FACTOR()) {
		if (lexemeList->front().getValue() == "+" or lexemeList->front().getValue() == "-") {
			lexemeList->pop_front();
			if (EXPR()) {
				return true;
			}
			else {
				tokens.pop_back();
				return false;
			}
		}
		
		return true;
	}
	else {
		tokens.pop_back();
		return false;
	}
}

//Rule 14 : FACTOR->OPERAND | OPERAND * FACTOR | OPERAND / FACTOR
bool grammar::FACTOR() {

	tokens.push_back("FACTOR");

	if (OPERAND()) {
		if (lexemeList->front().getValue() == "*" or lexemeList->front().getValue() == "/") {
			lexemeList->pop_front();
			if (OPERAND()) {
				return true;
			}
			else {
				tokens.pop_back();
				return false;
			}
		}

		return true;
	}
	else {
		tokens.pop_back();
		return false;
	}
}

//Rule 15 : OPERAND->NUM | ID | (EXPR)
bool grammar::OPERAND() {

	tokens.push_back("OPERAND");

	if (NUM()) {
		return true;
	}
	else if (ID()) {
		return true;
	}
	else {
		tokens.pop_back();
		return false;
	}
}

//Rule 16 : NUM -> (0 | 1 | ... | 9) + [.(0 | 1 | … | 9) + ]
bool grammar::NUM() {

	if (debugFlag) {
		tokens.push_back("DEBUG_NUM");
	}

	if (lexemeList->front().getTypeID() == NUMBER) {
		debugLex(lexemeList->front());
		lexemeList->pop_front();
	}
	else {
		//TODO FIX THIS
		errorMessage = "ERROR !! impropper number literal on line " + std::to_string(lexemeList->front().getSourceLine()) + '.';
		return false;
	}

	return true;
}

//Rule 17 : COMP -> (OPERAND = OPERAND) | (OPERAND <> OPERAND) | (OPERAND > OPERAND) | (OPERAND < OPERAND)
bool grammar::COMP() {

	//TODO
	tokens.push_back("COMP");

	return false;
}

//Rule 18 : TYPE -> int | float | double
bool grammar::TYPE() {

	if (debugFlag) {
		tokens.push_back("DEBUG_TYPE");
	}

	const std::string validTypes[3] = { "int", "float", "double" };

	for (int i = 0; i < 3; i++) {
		if (lexemeList->front().getValue() == validTypes[i]) {
			debugLex(lexemeList->front());
			lexemeList->pop_front();
			return true;
		}
	}

	return false;
}

bool grammar::checkSemicolon() {
	
	if (lexemeList->front().getValue() == ";") {
		debugLex(lexemeList->front());
		lexemeList->pop_front();
		return true;
	}
	else {
		errorMessage = "ERROR !! semicolon missing on line " + lexemeList->front().getSourceLine() + '.';
		return false;
	}
}