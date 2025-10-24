// CSCI 4355 Term Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//library includes
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

//program includes
#include "util.cpp"
#include "Lexeme.h"

/* instructions

- LEXEMES -
• Reserved words: program, begin, end, if, then, else, input, output, int, while, loop.

• Operators: assignment (:=), less than (<), greater than (>), equals (=), not equals (<>), plus (+), minus (-) , 
multiply (*), divide (/) and parentheses. The ‘;’ is also used to terminate statements and the ‘,’ and the ‘:’ are used 
when declaring variables.

• Identifiers: start with a letter or an ‘_’ followed by any number of letters, digits or underscores.

• Numbers: Either integer numbers (max 10 digits), or floating point numbers (max 10 digits).

- GRAMMAR -

Rule 01: PROGRAM -> program DECL_SEC begin STMT_SEC end; | program begin STMT_SEC end;
Rule 02: DECL_SEC -> DECL | DECL DECL_SEC
Rule 03: DECL -> ID_LIST : TYPE ;
Rule 04: ID_LIST -> ID | ID , ID_LISTRule 06: STMT_SEC à STMT | STMT STMT_SEC
*Rule 05: ID  (_ | a | b | … | z | A | … | Z) (_ | a | b | … | z | A | … | Z | 0 | 1 | … | 9)*
Rule 07: STMT -> ASSIGN | IFSTMT | WHILESTMT | INPUT | OUTPUT
Rule 08: ASSIGN -> ID := EXPR ;
Rule 09: IFSTMT -> if COMP then STMT_SEC end if ; | if COMP then STMT_SEC else STMT_SEC end if ;
Rule 10: WHILESTMT -> while COMP loop STMT_SEC end loop ;
Rule 11: INPUT -> input ID_LIST;
Rule 12: OUTPUT -> output ID_LIST; | output NUM;
Rule 13: EXPR -> FACTOR | FACTOR + EXPR | FACTOR - EXPR
Rule 14: FACTOR -> OPERAND | OPERAND * FACTOR | OPERAND / FACTOR
Rule 15: OPERAND -> NUM | ID | ( EXPR )
*Rule 16: NUM -> (0 | 1 | ... | 9)+ [.(0 | 1 | … | 9)+]
Rule 17: COMP -> ( OPERAND = OPERAND ) | ( OPERAND <> OPERAND ) | ( OPERAND > OPERAND ) | ( OPERAND < OPERAND )
*Rule 18: TYPE -> int | float | double
 
    *does not require implimentation

- ERRORS -
Upon encountering a variable in a declaration section, you must add it to the symbol table. This means that a 
redeclaration of a variable should produce an error and exit the program. The use of a variable before it is declared 
should also produce an error indicating an undeclared identifier and exit the program.

Other errors that could be generated upon scanning and parsing a program:
• Illegal symbol
• Illegal identifier
• Illegal number
• Parse errors encountered by expecting a symbol and not getting that symbol.

All errors must indicate the line number in the file. All error message must be descriptive as well indicating what 
happened precisely. Upon encountering an error, you must exit the program immediately after reporting the error and its 
location.

*/

//debug setting
const bool debugFlag = true;

int main()
{
    if (debugFlag) {
        std::cout << "##### DEBUGGING ON #####" << std::endl << std::endl;
    }

    //string for file user wants to analyze
    std::string userFilename = "test.txt";

    //get user filename
    //std::cout << "Enter file name: ";
    //std::getline(std::cin, userFilename);

    //msg
    std::cout << "Analyzing " << userFilename << std::endl << std::endl;

    //open input file stream
    std::ifstream sourceFile;
    sourceFile.open(userFilename);

    //string for current line being worked on
    std::string workingLine;

    std::vector<std::string> potentialLexemes;

    //TODO make this OR for loop  a function
    while (std::getline(sourceFile, workingLine)) {
        workingLine = workingLine + '\n';

        //
        std::string currentLexeme = "";

        //scan for potential lexemes
        for (int i = 0; i < workingLine.size(); i++) {

            //std::cout << workingLine[i] << std::endl;
            
            //check for symbols
            if (isOperator(workingLine[i])) {

                if (currentLexeme != "") {
                    potentialLexemes.push_back(currentLexeme);
                    currentLexeme = "";
                }

                currentLexeme = currentLexeme + workingLine[i];

                //check for multi symbol lexemes
                if (workingLine[i] == ':' and workingLine[i + 1] == '=') {
                    currentLexeme = currentLexeme + workingLine[i + 1];
                    i++;
                } else if (workingLine[i] == '<' and workingLine[i + 1] == '>') {
                    currentLexeme = currentLexeme + workingLine[i + 1];
                    i++;
                }

                potentialLexemes.push_back(currentLexeme);
                currentLexeme = "";

            } 
            else if (workingLine[i] != ' ') {

                currentLexeme = currentLexeme + workingLine[i];

                if (workingLine[i + 1] == ' ' || workingLine[i + 1] == '\n') {
                    potentialLexemes.push_back(currentLexeme);
                    currentLexeme = "";
                }

            }
        }
    }

    //debugging tool - print potential lexeme list
    if (debugFlag) {
        for (int i = 0; i < potentialLexemes.size(); i++) {
            std::cout << "potential lexeme: " << potentialLexemes[i] << std::endl;
        }
        std::cout << std::endl;
    }
    
    //convert lexeme strings into lexeme objects - merger with previous loop/function?
    std::vector<Lexeme> validLexemes;

    for (int i = 0; i < potentialLexemes.size(); i ++) {

        //check for reserved words
        if (isReservedWord(potentialLexemes[i])) {
            validLexemes.push_back(Lexeme(RESERVED_WORD, potentialLexemes[i]));
        }
        //check for identifiers
        else if (isalpha(potentialLexemes[i][0]) || potentialLexemes[i][0] == '_') {
                validLexemes.push_back(Lexeme(IDENTIFIER, potentialLexemes[i]));
        }
        //check for operators
        else if (isOperator(potentialLexemes[i][0])) {
            validLexemes.push_back(Lexeme(OPERATOR, potentialLexemes[i]));
        }

        //check for number literals
        for (int j = 0; j < potentialLexemes[i].size(); j++) {
            if (not std::isdigit(potentialLexemes[i][j])) {
                break;
            }
            else if (potentialLexemes[i].size() == j + 1) {
                validLexemes.push_back(Lexeme(NUMBER, potentialLexemes[i]));
            }
        }
    }
    
    //debugging tool - check lexeme vectors against each other
    if (debugFlag and potentialLexemes.size() != validLexemes.size()) {
        std::cout  << "##### LEXEME VECTORS DISCREPENCY #####" << std::endl << std::endl;
    }

    //debugging tool - print valid lexemes
    if (debugFlag) {
        for (int i = 0; i < validLexemes.size(); i++) {
            std::cout << validLexemes[i].getTypeStr() << ": " << validLexemes[i].getValue() << std::endl;
        }
        std::cout << std::endl;
    }

    std::cout << "Done :)" << std::endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
