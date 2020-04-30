namespace Tokenizer {

    enum TokenType {

        GLOBAL,

        SET,
        VAR,
        ON,
        OFF,
        DIGITAL,
        ANALOG,
        FUNCTION,

        OPEN_CURLY_BRACKET,
        CLOSED_CURLY_BRACKET,
        OPEN_SQUARE_BRACKET,
        CLOSED_SQUARE_BRACKET,
        OPEN_ROUND_BRACKET,
        CLOSED_ROUND_BRACKET,
    };

    using std::vector;
    using std::tuple;

    typedef tuple  <TokenType, vector <std::string>> Token;
    typedef vector <Token> Tokens;

    std::ifstream inFile;

    Tokens Tokenize(std::string src);

    std::string Load(std::string src_path){
        Logger::Dev("|g(T) |wFile path: |g" + src_path);
        
        inFile.open(src_path);
        
        if (!inFile) {
            Logger::Log( Error::Get("T000") );
            exit(1); 
        }
        
        std::string loaded_src =  std::string((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
        return loaded_src; 
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
           
            if( src[i] == '{'){ tokens.push_back({TokenType::OPEN_CURLY_BRACKET, {"{"}}); Logger::Dev("XD {");}
            if( src[i] == '}'){ tokens.push_back({TokenType::CLOSED_CURLY_BRACKET, {"}"}});   Logger::Dev("XD }");}

            
            if( src[i] == '['){ tokens.push_back({TokenType::OPEN_SQUARE_BRACKET, {"["}}); continue;}
            if( src[i] == ']'){ tokens.push_back({TokenType::CLOSED_SQUARE_BRACKET, {"]"}}); continue;}


            if( src[i] == '('){ tokens.push_back({TokenType::OPEN_ROUND_BRACKET, {"("}}); continue;}
            if( src[i] == ')'){ tokens.push_back({TokenType::CLOSED_ROUND_BRACKET, {")"}}); continue;}


            /*
            * Is this the normal way to handle variable declaration in tokenizer?
            * No, but it's easier to handle it in the tokenizer than in the AST.
            * I Kinda have a deadline on this project but I'll re-write a more efficient tokenizer later
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

                //Deleting spaces
                std::string::iterator end_pos = std::remove(var_sub.begin(), var_sub.end(), ' ');
                var_sub.erase(end_pos, var_sub.end());

                std::string variable_name = "";

                for(const auto c : var_sub){
                        if(c == '=') break;
                        variable_name = variable_name + c;
                }

                variable_name = variable_name.substr(3,variable_name.size());

                //Detecting variables that are assigned with no value
                if(variable_name[variable_name.size()-1] == ';'){
                    Token unassigned_variable = {TokenType::VAR, {variable_name.substr(0,variable_name.size()-1), "{novalue}"}}; 
                    tokens.push_back(unassigned_variable);
                    continue;
                }

                std::string var_statement = var_sub.substr(variable_name.size()+4,var_sub.size()-(variable_name.size()+5));
                
                //If it's a pin variable declaration like: var x = pin 40;
                if(var_statement.substr(0,3) == "pin"){
                    Token pin_variable = {TokenType::VAR, {variable_name, "pin", var_statement.substr(3,var_statement.size()-2)}};
                    tokens.push_back(pin_variable);
                    continue;
                }
                //If it's not a pin declaration, or an empty declaration... just add the token
                Token var_tkn = {TokenType::VAR, {variable_name, var_statement}};
                tokens.push_back(var_tkn);
                continue;
            }


            if(src.substr(i,9) == "function "){
                int placeholder_i = i;
                std::string on_substr;
                
                int nc = nearest_char('{',i,src);
                on_substr = src.substr(i,(nc+1)-i);
                i = nc-1;

                int parenthesis_start_index = nearest_char('(',placeholder_i,src);
                std::string fn_name = src.substr(placeholder_i + 9, (parenthesis_start_index) - (placeholder_i + 9));

                int parenthesis_end_index = nearest_char(')',(parenthesis_start_index) - (placeholder_i + 9),src);
                int prev_i = (parenthesis_start_index) - (placeholder_i + 9);
                std::string fn_params = src.substr(parenthesis_start_index+1, (parenthesis_end_index - parenthesis_start_index)-1);
                
                //We solve {content} inside the AST rn we just wanna push (FUNCTION, {"[FN_NAME]", "[PARAMS]"}) 
                Token fn_token = {TokenType::FUNCTION, {fn_name,fn_params}};
                tokens.push_back(fn_token);
                continue;
            }

            if(src.substr(i,5) == " set "){
                
                std::string set_substr;

                std::string set_name = "";
                std::string set_value = "";

                int nc = nearest_char(';',i,src);
                set_substr = src.substr(i,(nc+1)-i);
                int prev_i = i;
                i = nc;

                int set_name_index = nearest_char(';',prev_i,src);

                //Deleting spaces
                std::string::iterator end_pos = std::remove(set_substr.begin(), set_substr.end(), ' ');
                set_substr.erase(end_pos, set_substr.end());

                bool after_equals = false;

                for(const char k : set_substr){
                    if(k == '=') after_equals = true;

                    if(after_equals)
                        set_value = set_value += k;
                    else
                        set_name = set_name +=k;
                }

                set_name = set_name.substr(3,set_name.size()-3);
                set_value = set_value.substr(1,set_value.size()-2);

                Token set_token = {TokenType::SET, {set_name, set_value}};
                tokens.push_back(set_token);
                continue;
            }

            if(src.substr(i,4) == " on "){
                std::string on_substr;
                
                int nc = nearest_char(';',i,src);
                on_substr = src.substr(i,(nc+1)-i);
                i = nc;

                //Logger::Dev("ON: |p" + on_substr);
            }

        }
        Logger::Dev("|g(T) |w" + std::to_string(tokens.size()) + " tokens successfully generated");
        return tokens;
    }


}; 
