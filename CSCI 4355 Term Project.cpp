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
    std::string userFilename;

    //get user filename
    std::cout << "Enter file name: ";
    std::getline(std::cin, userFilename);

    //msg
    std::cout << "Analyzing " << userFilename;

    //open input file stream
    std::ifstream sourceFile;
    sourceFile.open(userFilename);

    //string for current line being worked on
    std::string workingLine;

    //get first line
    std::getline(sourceFile, workingLine);

    //list of lexemes
    std::vector<Lexeme> lexemesList;

    //index pointer for current line being worked on
    int workingLinePointer = 0;

    //parse current line loop
    for (int i = 0; i == workingLine.size(); i++) {

        //check for beginning of identifier or reserved word
        if (isAlphabetical(workingLine[workingLinePointer])) {
            //TODO HERE
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
