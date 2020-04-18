namespace Tokenizer {

    enum TokenType {

        INIT, 
        ASM, 
        IF, 
        ELSE, 
        SET, 
        INCREMENT, 
        VARIABLE, 
        FUNCTION, 
        CALL_FUNCTION

    };

    using std::vector;
    using std::tuple;

    typedef tuple  <TokenType, vector<std::string>> Token;
    typedef vector <Token> Tokens;

    std::ifstream inFile;
    std::string src_main;        

    int pos;

    void Tokenize(std::string src);

    void Load(std::string src_path){
        Logger::Dev("|g(T) |wFile path: |g" + src_path);
        
        inFile.open(src_path);
        
        if (!inFile) {
            Logger::Log( Error::T000 );
            exit(1); 
        }
        
        //converting ifstream to string
        src_main = std::string((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
        Tokenize(src_main);
    }   


    void findInSource(char c){

    }


    void Tokenize(std::string src){
        if(src.empty()) Logger::Panic (Error::T001);

        for(int i = 0; i < src.size(); i++){
            //std::cout << src[i];

            if(src.substr(i,3) == "var"){
                Logger::Dev("var found!");         
                for(int x = i; x < src.size(); x++){

                }

	        }


         }


    }


}; 
