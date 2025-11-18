//scanner.h

#pragma once

//library includes
#include <iostream>
#include <string>
#include <fstream>
#include <deque>

//project includes
#include "lexeme.h"
#include "grammar.h"
#include "utils.h"

//prototypes

class scanner {

private:

    //attributes
    std::ifstream sourceFile;
    std::string readLine;
    std::deque<char> lineSymbols;
    int lineNumber = 1;
    std::deque<lexeme> lexemes;

public:
    scanner(std::string userFileName);
    void findLexemes();
    void symbol();
    void number();
    void word();
    bool isNumLegal(char input);
    bool isWordLegal(char input);
    void illegalSymbol();
};