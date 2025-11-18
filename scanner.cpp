//scanner.cpp

#include "scanner.h"

scanner::scanner(std::string userFileName) {
    
    //msg
    std::cout << "Analyzing " << userFileName << std::endl << std::endl;

    sourceFile.open(userFileName);

    while (std::getline(sourceFile, readLine)) {

        //convert str to deque
        for (int i = 0; i < readLine.size(); i++) {
            lineSymbols.push_back(readLine[i]);
        }

        findLexemes();

        //incriment line number
        lineNumber++;
    }

    //run grammar logic
    grammar runGrammar(&lexemes);
}

void scanner::findLexemes() {
    while (not lineSymbols.empty()) {
        if (lineSymbols.front() == ' ') {
            lineSymbols.pop_front();
        }
        else if (isdigit(lineSymbols.front())) {
            number();
        }
        else if (isalpha(lineSymbols.front()) or lineSymbols.front() == '_') {
            word();
        }
        else if (isOperator(lineSymbols.front())) {
            symbol();
        }
        else {
            illegalSymbol(); }
    }
}

void scanner::number() {

    std::string workingLexeme = "";

    bool decimalFlag = false;

    workingLexeme.push_back(lineSymbols.front());
    lineSymbols.pop_front();

    while (not lineSymbols.empty() and isNumLegal(lineSymbols.front())) {

        if (lineSymbols.front() == '.') {
            if (decimalFlag) {
                std::cout << "ERROR !! illegal number on line " << lineNumber << '.';
                exit(2);
            }
            else {
                decimalFlag = true;
            }
        }
        

        workingLexeme.push_back(lineSymbols.front());
        lineSymbols.pop_front();
    }

    lexemes.push_back(lexeme(workingLexeme, lineNumber, NUMBER));
}

void scanner::word() {
    std::string workingLexeme = "";

    lexemeType type;

    workingLexeme.push_back(lineSymbols.front());
    lineSymbols.pop_front();

    while (not lineSymbols.empty() and isWordLegal(lineSymbols.front())) {

        workingLexeme.push_back(lineSymbols.front());
        lineSymbols.pop_front();
    }

    if (isReservedWord(workingLexeme)) {
        type = RESERVED_WORD;
    }
    else {
        type = IDENTIFIER;
    }

    lexemes.push_back(lexeme(workingLexeme, lineNumber, type));
}

void scanner::symbol() {
    
    std::string workingLexeme;

    workingLexeme.push_back(lineSymbols.front());
    lineSymbols.pop_front();

    if (workingLexeme == ":" and lineSymbols.front() == '=') {
        workingLexeme.push_back(lineSymbols.front());
        lineSymbols.pop_front();
    }
    else if (workingLexeme == "<" and lineSymbols.front() == '>') {
        workingLexeme.push_back(lineSymbols.front());
        lineSymbols.pop_front();
    }

    lexemes.push_back(lexeme(workingLexeme, lineNumber, OPERATOR));
}

bool scanner::isNumLegal(char input) {
    if (isdigit(input) or input == '.') {
        return true;
    }
    return false;
}

bool scanner::isWordLegal(char input) {
    if (isdigit(input) or isalpha(input) or input == '_') {
        return true;
    }
    return false;
}

void scanner::illegalSymbol() {
    std::cout << "ERROR !! illegal symbol \"" << lineSymbols.front() << "\" on line " << lineNumber << '.';
    exit(2);
}