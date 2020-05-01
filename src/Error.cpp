#pragma once

inline namespace Error {

    int currentLine;
    int currentChar;
    std::string additionalInfo = "";

    void updateLine(int lineNumber){ currentLine = lineNumber; }
    void updateChar(int charNumber){ currentChar = charNumber; }
    void updateAditionalInfo(std::string info){additionalInfo = info; }

    std::string Get(std::string err){

        /* Console Errors */
        if(err == "A000") return "|k" + err + " |rERROR: |wNo file or flags specified. Try using |pmicro --help";

        /* Tokenizer Errors */
        if(err == "T000") return "|k" + err + " |rERROR: |wNo source specified or wrong path";
        if(err == "T001") return "|k" + err + " |rERROR: |wSource file is empty";
        if(err == "T002") return "|k" + err + " |rERROR: |w Expected comma in line " + std::to_string(currentLine);   
        if(err == "T003") return "|k" + err + " |rERROR: |wexpected whitespace in line: " + std::to_string(currentLine) + " after 'var'";
        // if(err == "T004") return 
        // if(err == "T005") return 

        /* AST Errors */ 
        if(err == "AST001") return "|k" + err + " |rERROR: |wFailure to close scope on function " + additionalInfo + "()";

        return "";
    }

};