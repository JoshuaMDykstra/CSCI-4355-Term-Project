//grammar.cpp

#include "grammar.h"

//debugging tool
const bool debugFlag = false;

//constructor
grammar::grammar(std::deque<lexeme>* quePtr) {
	
	//take in pointer
	lexemeList = quePtr;

	//debugging tool
	if (debugFlag) { printLexemes(); }

	//run grammar logic
	if (not PROGRAM()) {

		//output tokens and error msg if failed
		grammarError();
	}
	else {

		//output tokens if succeed
		printTokens();
	}
}

//grammar error funtion
void grammar::grammarError() {

	printTokens();

	//print error msg and exit
	std::cout << errorMessage << std::endl;
	exit(3);
}

void grammar::printLexemes() {
	int lineNum = 0;

	for (int i = 0; i < lexemeList->size(); i++) {

		if (lineNum < lexemeList->at(i).getSourceLine()) {
			lineNum++;

			std::cout << std::endl << "Line " << lineNum << ": ";
		}

		std::cout << "\"" << lexemeList->at(i).getValue() << "\" ";
	}

	std::cout << std::endl << std::endl;
}

//print token function
void grammar::printTokens() {

	//loop through token vector and print them
	for (int i = 0; i < tokens.size(); i++) {

		if (debugFlag) {

			if (i < 9) {
				std::cout << " ";
			}

			std::cout << i + 1 << "   ";
		}

		std::cout << tokens[i] << std::endl;
	}
}

//Rule 01: PROGRAM->program DECL_SEC begin STMT_SEC end; | program begin STMT_SEC end;
bool grammar::PROGRAM() {
	
	//add token to list
	tokens.push_back("PROGRAM");

	//check for program keyword
	if (not checkLexeme("program")) {
		grammarError();
	}

	//run DECL_SEC if one exists
	DECL_SEC();

	//check for begin keyword
	if (not checkLexeme("begin")) {
		grammarError();
	}

	declerationSectionFlag = false;

	//run STMT_SEC logic, return false if fail
	if (not STMT_SEC()) {
		return false;
	}

	//check for end keyword and semicolon
	if (not checkLexeme("end")) {
		grammarError();
	}
	if (not checkLexeme(";")) {
		tokens.pop_back();
		return false;
		}

	//return true on success
	return true;
}

//Rule 02: DECL_SEC->DECL | DECL DECL_SEC
bool grammar::DECL_SEC() {

	//add token to list
	tokens.push_back("DECL_SEC");

	if (not DECL()) {
		tokens.pop_back();
		return false;
	}

	DECL_SEC();

	return true;
}

//Rule 03 : DECL->ID_LIST : TYPE;
bool grammar::DECL() {

	//add token to list
	tokens.push_back("DECL");

	//fail and remove token if ID_LIST not found
	if (not ID_LIST()) {
		tokens.pop_back();
		return false;
	}
	
	//check for colon
	if (not checkLexeme(":")) {
		tokens.pop_back();
		return false;
	}

	//check for TYPE, return false if fail
	if (not TYPE()) {
		tokens.pop_back();
		return false;
	}

	//check for semicolon
	if (not checkLexeme(";")) {
		return false;
	}

	//return true on success
	return true;
}

//Rule 04: ID_LIST->ID | ID, ID_LIST
bool grammar::ID_LIST() {

	//add token to list
	tokens.push_back("ID_LIST");

	//fail if ID not found
	if (ID()) {

	//check for another ID_LIST if comma found
		if (checkLexeme(",")) {
			ID_LIST();
		}
		return true;
	}
	else {
		tokens.pop_back();
		return false;
	}
}

//Rule 05 : ID(_ | a | b | … | z | A | … | Z) (_ | a | b | … | z | A | … | Z | 0 | 1 | … | 9) *
bool grammar::ID() {

	//fail if lexeme type id is incorrect
	if (lexemeList->front().getTypeID() != IDENTIFIER) {
		return false;
	}

	//if in decleration section, add identifier to list of declared identifiers and return true
	if (declerationSectionFlag) {
		declaredIdentifiers.push_back(lexemeList->front().getValue());
		lexemeList->pop_front();
		return true;
	}
	else {
		//if not in decleration section and identifier was previously declared return true, exit if not
		if (identifierDeclared()) {
			lexemeList->pop_front();
			return true;
		}
		else {
			errorMessage = "ERROR !! identifier \"" + lexemeList->front().getValue() + "\" not declared in line " + std::to_string(lexemeList->front().getSourceLine()) + '.';
			grammarError();
		}
	}
}

//Rule 06: STMT_SEC->STMT | STMT STMT_SEC
bool grammar::STMT_SEC() {

	//add token to list
	tokens.push_back("STMT_SEC");

	//check for STMT
	if (STMT()) {

		//try to find another STMT_SEC, ignore failure 
		STMT_SEC();

		//return true on success
		return true;
	}
	//return false and remove token if fail
	else {
		tokens.pop_back();
		return false;
	}
}

//Rule 07 : STMT->ASSIGN | IFSTMT | WHILESTMT | INPUT | OUTPUT
bool grammar::STMT() {

	//add token to list
	tokens.push_back("STMT");

	//check for all statement types, fail if none found
	if (ASSIGN() || IFSTMT() || WHILESTMT() || INPUT() || OUTPUT()) {
		return true;
	}
	else {
		//return false and remove token if fail
		tokens.pop_back();
		return false;
	}
}

//Rule 08 : ASSIGN->ID := EXPR;
bool grammar::ASSIGN() {

	//add token to list
	tokens.push_back("ASSIGN");

	//check for ID
	if (not ID()) {
		tokens.pop_back();
		return false;
	}

	//check for := oporator
	if (not checkLexeme(":=")) {
		tokens.pop_back();
		return false;
	}
	
	//check for EXPR and semicolon
	if (not EXPR()) {
		tokens.pop_back();
		return false;
	}
	if (not checkLexeme(";")) {
		grammarError();
	}

	//retrun true if all checks pass
	return true;
}

//Rule 09: IFSTMT -> if COMP then STMT_SEC end if; | if COMP then STMT_SEC else STMT_SEC end if;
bool grammar::IFSTMT() {

	tokens.push_back("IFSTMT");

	//check for if keyword
	if (not checkLexeme("if")) {
		tokens.pop_back();
		return false;
	}

	//check for COMP
	if (not COMP()) {
		tokens.pop_back();
		return false;
	}

	//check for then keyword
	if (not checkLexeme("then")) {
		grammarError();
	}

	//check for STMT_SEC
	if (not STMT_SEC()) {
		tokens.pop_back();
		return false;
	}

	//check for else keyword
	if (checkLexeme("else")) {
		if (not STMT_SEC()) {
			tokens.pop_back();
			return false;
		}
	}

	//check for end keyword
	if (not checkLexeme("end")) {
		grammarError();
	}

	//check for if keyword
	if (not checkLexeme("if")) {
		grammarError();
	}

	//check for semicolon
	if (not checkLexeme(";")) {
		grammarError();
	}

	//return true if all checks passed
	return true;
}

//Rule 10: WHILESTMT -> while COMP loop STMT_SEC end loop;
bool grammar::WHILESTMT() {

	tokens.push_back("WHILESTMT");

	//check for while keyword
	if (not checkLexeme("while")) {
		tokens.pop_back();
		return false;
	}
	
	//check for COMP
	if (not COMP()) {
		tokens.pop_back();
		return false;
	}

	//check for loop keyword
	if (not checkLexeme("loop")) {
		grammarError();
	}

	//check for STMT_SEC
	if (not STMT_SEC()) {
		tokens.pop_back();
		return false;
	}

	//check for end keyword
	if (not checkLexeme("end")) {
		grammarError();
	}

	//check for loop keyword
	if (not checkLexeme("loop")) {
		grammarError();
	}

	//check for semicolon
	if (not checkLexeme(";")) {
		grammarError();
	}

	return true;
}

//Rule 11: INPUT->input ID_LIST;
bool grammar::INPUT() {
	
	//add token to list
	tokens.push_back("INPUT");

	//check for input keyword
	if (not checkLexeme("input")) {
		tokens.pop_back();
		return false;
	}
	
	//check for ID_LIST
	if (not ID_LIST()) {
		tokens.pop_back();
		return false;
	}
	
	//check for semicolon
	if (not checkLexeme(";")) {
		grammarError();
	}

	return true;
}

//Rule 12: OUTPUT->output ID_LIST; | output NUM;
bool grammar::OUTPUT() {

	//add token to list
	tokens.push_back("OUTPUT");

	//check for output keyword
	if (not checkLexeme("output")) {
		tokens.pop_back();
		return false;
	}

	//check for ID_LIST or NUM
	if (not NUM() and not ID_LIST()) {
		tokens.pop_back();
		return false;
	}

	//check for semicolon
	if (not checkLexeme(";")) {
		grammarError();
	}

	return true;
}

//Rule 13: EXPR->FACTOR | FACTOR + EXPR | FACTOR - EXPR
bool grammar::EXPR() {

	//add token to list
	tokens.push_back("EXPR");

	//check for FACTOR
	if (FACTOR()) {

		//check for second EXPR if + or - operators found
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
		
		//return true regardless of EXPR check
		return true;
	}
	//return false and remove token on fail
	else {
		tokens.pop_back();
		return false;
	}
}

//Rule 14 : FACTOR->OPERAND | OPERAND * FACTOR | OPERAND / FACTOR
bool grammar::FACTOR() {

	//add token to list
	tokens.push_back("FACTOR");

	//check for OPERAND
	if (OPERAND()) {

		//check for FACTOR if * or / operators found
		if (lexemeList->front().getValue() == "*" or lexemeList->front().getValue() == "/") {
			lexemeList->pop_front();
			if (FACTOR()) {
				return true;
			}
			else {
				tokens.pop_back();
				return false;
			}
		}

		//return true regardless of FACTOR check
		return true;
	}
	//return false and remove token on fail
	else {
		tokens.pop_back();
		return false;
	}
}

//Rule 15 : OPERAND->NUM | ID | (EXPR)
 bool grammar::OPERAND() {

	//add token to list
	tokens.push_back("OPERAND");

	//check for NUM or ID
	if (NUM()) {
		return true;
	}
	else if (ID()) {
		return true;
	}
	//return false and remove token on fail
	else {
		tokens.pop_back();
		return false;
	}
}

//Rule 16 : NUM -> (0 | 1 | ... | 9) + [.(0 | 1 | … | 9) + ]
bool grammar::NUM() {

	//check lexeme is NUMBER type
	if (lexemeList->front().getTypeID() == NUMBER) {
		lexemeList->pop_front();
	}
	//return false on fail
	else {
		return false;
	}

	return true;
}

//Rule 17 : COMP -> (OPERAND = OPERAND) | (OPERAND <> OPERAND) | (OPERAND > OPERAND) | (OPERAND < OPERAND)
bool grammar::COMP() {

	tokens.push_back("COMP");

	//check for open parenthases
	if (not checkLexeme("(")) {
		tokens.pop_back();
		return false;
	}

	//check for OPERAND
	if (not OPERAND()) {
		tokens.pop_back();
		return false;
	}

	//const array of valid types
	const std::string validOperators[4] = { "=", "<>", ">", "<"};

	//check for valid operator
	for (int i = 0; i < 3; i++) {
		if (lexemeList->front().getValue() == validOperators[i]) {
			lexemeList->pop_front();
			break;
		}
	}

	//check for OPERAND
	if (not OPERAND()) {
		tokens.pop_back();
		return false;
	}

	//check for closed parenthases
	if (not checkLexeme(")")) {
		tokens.pop_back();
		return false;
	}

	return true;
}

//Rule 18 : TYPE -> int | float | double
bool grammar::TYPE() {

	//const array of valid types
	const std::string validTypes[3] = { "int", "float", "double" };

	//return true if lexeme matches a valid type
	for (int i = 0; i < 3; i++) {
		if (lexemeList->front().getValue() == validTypes[i]) {
			lexemeList->pop_front();
			return true;
		}
	}
	
	//return false if fail
	return false;
}

bool grammar::checkLexeme(std::string word) {
	
	//pop lexeme and return true if next lexeme if semicolon
	if (lexemeList->front().getValue() == word) {
		lexemeList->pop_front();
		return true;
	}
	//return false on fail
	else if (word != "end") {

		//error msg and fail
		if (word == ";") {
			errorMessage = "ERROR !! semicolon missing on line " + std::to_string(lexemeList->front().getSourceLine()) + '.';
		}
		else {
			errorMessage = "ERROR !! " + word + " missing on line " + std::to_string(lexemeList->front().getSourceLine()) + '.';
		}

		return false;
	}
	else { return false; }
}

bool grammar::identifierDeclared() {
	//loop through list of declared identifiers
	for (int i = 0; i < declaredIdentifiers.size(); i++) {
		//return true if front lexeme in declared identifiers

		if (declaredIdentifiers[i] == lexemeList->front().getValue()) {
			return true;
		}
	}

	//fail otherwise
	return false;
}