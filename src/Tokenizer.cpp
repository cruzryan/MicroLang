namespace Tokenizer {

    enum TokenType {
        SYMBOL,
        SET,
        OPERATION,
        CLOSED_BRACKET,
        OPEN_BRACKET,
        VAR
    };

    using std::vector;
    using std::tuple;

    typedef tuple  <TokenType, vector <std::string>> Token;
    typedef vector <Token> Tokens;

    std::ifstream inFile;
    std::string src_main;        

    Tokens Tokenize(std::string src);

    void Load(std::string src_path){
        Logger::Dev("|g(T) |wFile path: |g" + src_path);
        
        inFile.open(src_path);
        
        if (!inFile) {
            Logger::Log( Error::Get("T000") );
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

    //To keep track of what line in the file we are
    int line = 1;

    Tokens Tokenize(std::string src){

        Tokens tokens;
        
        if(src.empty()) Logger::Panic (Error::Get("T001"));

        for(int i = 0; i < src.size(); i++){
            
            if( src[i] == '\n' || src[i] == '\r' ) line += 1;
            
            /*
            * Is this the normal way to handle variable declaration in tokenizer?
            * No, but it's easier to handle it in the tokenizer than in the AST.
            */

            if(src.substr(i,3) == "var"){
                
                std::string var_sub;
                
                int nc = nearest_char(';',i,src);
                var_sub = src.substr(i,(nc+1)-i);
                i = nc;

                //Making sure there is a space between the word var and the statement
                if(var_sub[3] != ' '){
                    Logger::Dev("line: " + std::to_string(line));
                    Error::updateLine(line);
                    Logger::Panic( Error::Get("T003") );
                }
                //Eliminar espacios

                std::string::iterator end_pos = std::remove(var_sub.begin(), var_sub.end(), ' ');
                var_sub.erase(end_pos, var_sub.end());

                //Dividir el statement antes y despues de la asignacion de la variable

                std::string variable_name = "";

                for(const auto c : var_sub){
                        if(c == '=') break;
                        variable_name = variable_name + c;
                }

                ///TODO: I'll fix this mess later
                int variable_name_length = variable_name.size() - 3;

                Logger::Dev("var name: " + variable_name);

                //Detecting variables that are assigned with no value
                if(variable_name[variable_name.size()-1] == ';'){
                    variable_name = variable_name.substr(3,variable_name.size()-4);
                    Logger::Dev("added: |g" + variable_name);
                    Token unassigned_variable = {TokenType::VAR, {variable_name, "{novalue}"}}; 
                    tokens.push_back(unassigned_variable);
                    continue;
                }

                // Logger::Dev(std::to_string(variable_name_length));

                //Logger::Dev(var_sub.substr(5,var_sub.size()) + "in line: " + std::to_string(line));

                tokens.push_back({TokenType::VAR, {"",""}});
            }

        
        }

        return tokens;
    }


}; 
