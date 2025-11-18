CSCI 4355 Term Project
Joshua Dykstra


Files:
    CSCI 4355 Term Project.cpp (main)
    lexeme.h
    lexeme.cpp
    scanner.h
    scanner.cpp
    grammar.h
    grammar.cpp
    utils.h
    utils.cpp
    README.md


This program propts the user for a filename and attempts to perform lexical analyis. It only searches its current
directory for files. It does not check to see if the file actually exists and will crash if it fails to find one.


There is a debug setting in grammar.cpp on line 6. This setting causes the program to print a list of scanned lexemes
organized by line as well as add line numbering to the printed tokens.


The program was tested with all 6 provided test cases and successfully matched their output. It was also tested with 
several modified version of test case 1.


A github repository for this project can be found at: https://github.com/JoshuaMDykstra/CSCI-4355-Term-Project