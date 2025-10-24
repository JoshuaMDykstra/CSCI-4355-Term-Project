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

	//Reserved words: program, begin, end, if, then, else, input, output, int, while, loop.
	const std::string reservedWords[11] = { "program", "begin", "end", "if", "then", "else", "input", "output", "int", "while", "loop" };

	//hardcode i < 11; .size() and .sizeof() both break here?????
	for (int i = 0; i < 11; i++) {
		if (input == reservedWords[i]) {
			return true;
		}
	}

	return false;
}

