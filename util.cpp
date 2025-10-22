#pragma once

#include <string>

//bool function to check if char is in aphabet ignoring case
bool isSymbol(char target, char type) {
	
	std::string list = "";

	switch (type) {

	case 'A':
		list = { "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ" };
		break;
	case 'N':
		list = { "0123456789" };
		break;
	case 'O':
		list = { ":=<>+-*/():;," };
		break;
	}

	for (int i = 0; i < list.size(); i++) {
		if (target == list[i]) {
			return true;
		}
	}

	return false;
}