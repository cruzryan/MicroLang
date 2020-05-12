namespace AST {

	using namespace Tokenizer;
	using std::cout;
	using std::endl;
	using std::vector;

	Tokens globalTokens;
	int i = 0;

	struct Node {
		
		vector<struct Node*> nodes;
		Tokenizer::TokenType tokentype;
		std::string tokenstr;

		void insert(struct Node *x){
			if(x == nullptr) return;
			this->nodes.push_back(x);
		}

		int getNumberOfNodes(){
			return this->nodes.size();
		}

		Node* getNode(int index){
			return this->nodes[index];
		}
		
		std::string getstr(){
			return this->tokenstr;
		}

 		Node(){}
		~Node() = default;
	};


	struct Function : Node {
		std::vector<std::string> params;
		Function(std::vector<std::string> params){
			this->params = params;		
			this->tokentype = TokenType::FUNCTION;
			this->tokenstr = "fn";
		}
	};

	struct Variable : Node {
		std::string type;
		std::string var_name;
		std::string value;
			
		Variable(Tokenizer::TokenType tt, std::string type, std::string var_name, std::string value){
			this->tokentype = tt;
			this->type = type;
			this->var_name = var_name;
			this->value = value;
			this->tokenstr = "var";
		}
	};

	std::string getTypeOfVar(std::string statement){
		if(statement[0] == '"' && statement[statement.size()-1] == '"' ) return "string";
		if(statement.substr(0,2) == "0x") return "hex";
		if(strspn( statement.c_str(), "-.0123456789" ) == statement.size() ) return "number";	
		if(statement == "true" || statement == "false") return "bool";
		if(statement == "{novalue}") return "undefined";
		for(const char c : statement){
			//Check if it's an operation
			if(c == '+' || c == '-' || c == '*' || c == '/' || c == '&' || c == '|' || c == '(' || c == ')'){
				return "operation";
			}		
		}
		return "not-known";
	}

	Node* GenNode(Token tkn, int pos, bool scoped = false){

		//Remember, tokens are just tuples, where the first parameter (0) in the tuple is the TokenType
		auto token_type = std::get<0>(tkn);

		switch(token_type){

			case TokenType::VAR: {

				std::string var_name = std::get<1>(tkn)[0]; 
				if(std::get<1>(tkn)[1] == std::string("pin")){
					Variable* pin_var_node = new Variable(token_type, "pin", var_name, std::get<1>(tkn)[2]);
					return pin_var_node;
				}

				//If it's not a pin variable, let's check what's going on in the statement
				std::string statement = std::get<1>(tkn)[1];
				Variable* varnode = new Variable(token_type, "", var_name, statement);
				varnode->type = getTypeOfVar(statement);
				return varnode;

			}break;

			case TokenType::SET: {
				
				Token newtoken = tkn;
				//Trick GenNode into thinking we're generating a variable node
				std::get<0>(newtoken) = TokenType::VAR;
				Node* set_node = GenNode(newtoken, pos);
				//Change the variable parameters to the "set" parameters
				set_node->tokentype = TokenType::SET;
				set_node->tokenstr = "set";

				/*
				You might wonder what's the point of generating two nearly identical nodes,
				well, althought they are similar, the assembly for each will differ vastly
				*/

				return set_node;
			}break;

			case TokenType::FUNCTION: {
				int ref = 0;
				int end_scope_pos = -1;

				//Search next tokens & keep val reference, this code might be cursed
				for(int t=pos; t < globalTokens.size(); t++){
					if(std::get<0>(globalTokens[t]) == TokenType::OPEN_CURLY_BRACKET){
						ref+=1;
					}
					if(std::get<0>(globalTokens[t]) == TokenType::CLOSED_CURLY_BRACKET){
						if(ref == 1){
							end_scope_pos = t+1;
							break;
						}else{
							ref-=1;
						}
					}
				}	

				//If user didn't close the scope panic!
				if(end_scope_pos == -1){
					//Tell Error the additional info we want is the name of the function
					std::string function_name = std::get<1>(tkn)[0];
					Error::updateAditionalInfo(function_name);
					Logger::Panic( Error::Get("AST001") );
				}else{ //If there is a scope:
				

					//Assign function parameters ex. function lol(x,y,z) it would be x,y,z
					std::vector<std::string> params;
					std::string cur_param = "";
					std::string fnParamsFromToken = std::get<1>(tkn)[1]; 

					for(int y = 0; y < fnParamsFromToken.size(); y++){
						if(fnParamsFromToken[y] == ','){
							params.push_back(cur_param);
							cur_param = "";
						}else{
							if(fnParamsFromToken[y] == ' ') continue;
							cur_param += fnParamsFromToken[y];
							if(y == (fnParamsFromToken.size()-1)){
								params.push_back(cur_param);
							}
						}
					}

					Function* fn = new Function(params);

					int token_at_index = 0;

					//For all tokens INSIDE the function scope
					for(int k=pos+2; k < end_scope_pos-1; k++){ //YOU NEED TO MODIFY SHIT HERE
						//Generate & Add the node to our function Node
						Node* fnNodeToAdd = GenNode(globalTokens[k], k, true);
						if(fnNodeToAdd == nullptr) continue;

						///TODO: FIX THIS WHEN IT's NESTED INSIDE 3 SCOPES
						if(fnNodeToAdd->tokentype == TokenType::FUNCTION){
							k = k + fnNodeToAdd->getNumberOfNodes()+1;
						}
						fn->insert(fnNodeToAdd);
					}
					
					//Tell i to skip all tokens inside the scope so we dont add nodes twice
					if(!scoped) i = i + ((end_scope_pos-pos) - (1));

					return fn;
					}				
					
				}break;

			default: break;
		}

		//If we're returning this, something went wrong
		return nullptr;
	}

	void printNodes(Node* node, int spacesCount){
		for(int n = 0; n < node->getNumberOfNodes(); n++){
			auto tempNode = node->getNode(n);

			std::string spaces = "";
			for(i = 0; i < spacesCount*2; i++) spaces += " ";

			if(tempNode->getNumberOfNodes() != 0){
				Logger::Dev("|k" + spaces + "L |b" + tempNode->tokenstr);
				printNodes(tempNode, spacesCount+1);
			}else{
				Logger::Dev("|k" + spaces + "|| |b" + tempNode->tokenstr);
			}
		}

	}

	Node* MakeAST(Tokens tkns){
		Logger::Dev("|p(AST) |wStarting AST with " + std::to_string(tkns.size()) + " tokens");
		globalTokens = tkns;
		
		Node* global = new Node();
		global->tokentype = TokenType::GLOBAL;

		for(i; i < tkns.size(); i++){
			Token tkn = tkns[i];
			Node* nodeToAdd = GenNode(tkns[i], i);
			global->insert(nodeToAdd);
		}

		printNodes(global, 1);
		Logger::Dev("|p(AST) |wNode tree successfully generated");

		return global;
	}

}