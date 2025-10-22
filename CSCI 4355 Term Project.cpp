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

int main()
{
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

    while (std::getline(sourceFile, workingLine)) {
        workingLine = workingLine + '\n';

        //
        std::vector<std::string> potentialLexemes;
        std::string currentLexeme = "";

        //scan for potential lexemes
        for (int i = 0; i < workingLine.size(); i++) {

            //std::cout << workingLine[i] << std::endl;
            
            //check for symbols
            if (isSymbol(workingLine[i], 'O')) {

                if (currentLexeme != "") {
                    potentialLexemes.push_back(currentLexeme);
                    currentLexeme = "";
                }

                currentLexeme = currentLexeme + workingLine[i];

                //check for multi symbol lexemes
                if (workingLine[i] == ':' && workingLine[i + 1] == '=') {
                    currentLexeme = currentLexeme + workingLine[i + 1];
                    i++;
                } else if (workingLine[i] == '<' && workingLine[i + 1] == '>') {
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

        for (int i = 0; i < potentialLexemes.size(); i++) {
            std::cout << "lexeme: " << potentialLexemes[i] << std::endl;
        }
    }
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
