#pragma once

inline namespace Error {

    int currentLine;
    int currentChar;

    void updateLine(int lineNumber ){ currentLine = lineNumber; }
    void updateChar(int charNumber ){ currentChar = charNumber; }

    const std::string
    
    /* Console Errors */
    A000 = "|kA0000 |rERROR: |wNo file or flags specified. Try using |pmicro --help",


    /* Tokenizer Errors */

    T000 = "|kT0000 |rERROR: |wNo source specified or wrong path",
    T001 = "|kT0001 |rERROR: |wSource file is empty",
    T002 = "Expected comma in line " + std::to_string(currentLine),
    T003 = "Something else",
    

    /* Compiler Errors */

    C001 = "Something";

};