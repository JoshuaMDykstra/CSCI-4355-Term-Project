#include "scanner.h"

void scan(std::string userFileName) {
    //msg
    std::cout << "Analyzing " << userFileName << std::endl << std::endl;

    //open input file stream
    std::ifstream sourceFile;
    sourceFile.open(userFileName);

    //string for current line being worked on
    std::string workingLine;

    //vector to store lexemes
    std::deque<lexeme> lexemes;

    //line tracker
    int lineNumber = 0;

    //TODO make this OR for loop  a function
    while (std::getline(sourceFile, workingLine)) {
        //account for getline removing newline char
        workingLine = workingLine + '\n';

        //string for working lexeme
        std::string currentLexeme = "";

        //scan for potential lexemes
        for (int i = 0; i < workingLine.size(); i++) {

            //std::cout << workingLine[i] << std::endl;

            //check for symbols
            if (isOperator(workingLine[i])) {

                //clear empty lexeme
                if (currentLexeme != "") {
                    lexemes.push_back(lexeme(currentLexeme, lineNumber));
                    currentLexeme = "";
                }

                //add current char to working lexeme
                currentLexeme = currentLexeme + workingLine[i];

                //check for multi symbol lexemes := and <>
                if (workingLine[i] == ':' and workingLine[i + 1] == '=') {
                    currentLexeme = currentLexeme + workingLine[i + 1];
                    i++;
                }
                else if (workingLine[i] == '<' and workingLine[i + 1] == '>') {
                    currentLexeme = currentLexeme + workingLine[i + 1];
                    i++;
                }

                //add finished lexeme to vector and reset
                lexemes.push_back(lexeme(currentLexeme, lineNumber));
                currentLexeme = "";

            }

            //check for alphanumeric symbol
            else if (workingLine[i] != ' ') {

                currentLexeme = currentLexeme + workingLine[i];

                //push working lexeme to vector if next symbol is space
                if (workingLine[i + 1] == ' ' || workingLine[i + 1] == '\n') {
                    lexemes.push_back(lexeme(currentLexeme, lineNumber));
                    currentLexeme = "";
                }

            }
        }

        //incriment line number
        lineNumber++;
    }

    //debugging tool - print lexemes
    if (debugFlag) {
        for (int i = 0; i < lexemes.size(); i++) {
            std::cout << lexemes[i].getTypeStr() << ": " << lexemes[i].getValue() << std::endl;
        }
        std::cout << std::endl;
    }

    //run grammar logic
    grammar runGrammar(&lexemes);
	}