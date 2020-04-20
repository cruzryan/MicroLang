namespace Tokenizer {

    enum TokenType {
        SYMBOL,
        SET,
        OPERATION,
        CLOSED_BRACKET,
        OPEN_BRACKET
    };

    using std::vector;
    using std::tuple;

    typedef tuple  <TokenType, vector <std::string>> Token;
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


    int nearest_char(char c, int pos, std::string source){
        for(int i = pos; i < source.size(); i++){
            if(source[i] == c){
                return i;
            }
        }
        return 0;
    }

    void Tokenize(std::string src){

        Tokens tokens;
        
        if(src.empty()) Logger::Panic (Error::T001);

        for(int i = 0; i < src.size(); i++){

            // if(src.substr(i,))
            
            if(src.substr(i,3) == "var"){
                
                std::string var_sub;
                
                int nc = nearest_char(';',i,src);
                var_sub = src.substr(i,(nc+1)-i);
                i = nc+1;


                tokens.push_back({TokenType::SET, {"",""}});
            }

        
        
        }
    }


}; 
