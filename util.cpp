#pragma once

#include <string>

//bool function to check if char is in aphabet ignoring case
bool isOperator(char target) {
	
	const std::string list = { ":=<>+-*/():;," };
	
	for (int i = 0; i < list.size(); i++) {
		if (target == list[i]) {
			return true;
		}
	}

	return false;
}

//bool function to check if str is a reserved word
bool isReservedWord(std::string input) {

	const std::string reservedWords[9] = { "begin", "else", "end", "if", "input", "int", "loop", "output", "while" };

	for (int i = 0; i < 9; i++) {
		if (input == reservedWords[i]) {
			return true;
		}
	}

	return false;
}

