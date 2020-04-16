#pragma once

inline namespace Error {

    int currentLine;
    int currentChar;

    void updateLine(int lineNumber ){ currentLine = lineNumber; }
    void updateChar(int charNumber ){ currentChar = charNumber; }

    const std::string
    
    /* Console Errors */
    A0000 = "|kA0000 |rERROR: |wNo file or flags specified. Try using |pmicro --help",


    /* Parser Errors */
    //|pmicro your_file.micro -o output.asm

    P0001 = "Expected comma in line " + std::to_string(currentLine),
    P0002 = "Something else",
    

    /* Compiler Errors */

    C0001 = "Something";

};