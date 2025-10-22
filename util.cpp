#pragma once

#include "CSCI 4355 Term Project.cpp"

//bool function to check if char is in aphabet ignoring case
bool isAlphabetical(char target) {
	
	const std::string alphabet = { "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ" };

	for (int i = 0; i < 52; i++) {
		if (target == alphabet[i]) {
			return true;
		}
	}

	return false;
}