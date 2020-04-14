inline class Error {
    
    public:

    void updateLine(int lineNumber ){ this->currentLine = lineNumber; }
    void updateChar(int charNumber ){ this->currentChar = charNumber; }

    void getError(ErrorType error){ return errors[error] }

    private:

    int currentLine;
    int currentChar;

    const std::string errors[] = {
        

    }

    const std::string
    
    /* Parser Errors */

    P0001 = "Expected comma in line " + std::to_string(currentLine),
    P0002 = "Something else",
    

    /* Compiler Errors */

    C0001 = "Something"

} 