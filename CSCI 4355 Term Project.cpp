// CSCI 4355 Term Project.cpp

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
Rule 06: STMT_SEC -> STMT | STMT STMT_SEC
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

//library includes
#include <iostream>
#include <string>
#include <filesystem>

//project includes
#include "scanner.h"

int main()
{
    //string for file user wants to analyze
    std::string inputFile;

    //prompt user for filename
    std::cout << "Enter file name: ";
    std::getline(std::cin, inputFile);
    
    scanner runScanner(inputFile);

    //exit message
    std::cout << std::endl << "Done :)" << std::endl;
}