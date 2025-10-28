#include "utils.h"

//bool function to check if char is in aphabet ignoring case
bool isOperator(char target) {

    //const array of valid operator symbol
    const std::string list = { ":=<>+-*/():;," };

    //loop through list return true if input matches a valid operator symbol
    for (int i = 0; i < list.size(); i++) {
        if (target == list[i]) {
            return true;
        }
    }

    //return false if fail
    return false;
}

//bool function to check if str is a reserved word
bool isReservedWord(std::string input) {

    //Reserved words: program, begin, end, if, then, else, input, output, int, while, loop.
    const std::string reservedWords[11] = { "program", "begin", "end", "if", "then", "else", "input", "output", "int", "while", "loop" };

    //loop through reserved word and retunr true if one matches input
    for (int i = 0; i < 11; i++) {  //have to hardcode i < 11; .size() and .sizeof() both break here?????
        if (input == reservedWords[i]) {
            return true;
        }
    }

    //return false on fail
    return false;
}