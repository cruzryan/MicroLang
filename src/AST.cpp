namespace AST {

		using namespace Tokenizer; //To access Tokens & Token type defintions

        struct Node {
			
        	std::vector<std::shared_ptr<struct Node*>> nodes;
            Tokenizer::TokenType tokentype;

			//insert node
			void insert(Node* x){
				this->nodes.push_back(std::make_shared<Node*>(x));
			}

			auto getNode(int index){
				return *nodes[index].get(); 
			}

			virtual ~Node() = default;

        };

		struct Function : Node {
			std::vector<std::string> params;
			Function(std::vector<std::string> params){
				this->params = params;				
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
			}
		};

		struct If : Node {
			std::string statement;
			Node* else_node; //if there is no else, else_node will be NULL
		};

		Tokens globalTokens;
		int i = 0;

		std::string getTypeOfVar(std::string statement){
			if(statement[0] == '"' && statement[statement.size()-1] == '"' ) return "string";
			if(statement.substr(0,2) == "0x") return "hex";
			if(strspn( statement.c_str(), "-.0123456789" ) == statement.size() ) return "number";	
			if(statement == "true" || statement == "false") return "bool";

			for(const char c : statement){
				//Check if it's an operation
				if(c == '+' || c == '-' || c == '*' || c == '/' || c == '&' || c == '|' || c == '(' || c == ')'){
					return "operation";
				}		
			}
					
			return "undefined";
		}

		Node GenNode(Token tkn, int pos){
			
			//Remember, tokens are just tuples, where the first parameter (0) in the tuple is the TokenType
			auto token_type = std::get<0>(tkn);

			switch(token_type){

				case TokenType::VAR: {
					std::string var_name = std::get<1>(tkn)[0]; 

					if(std::get<1>(tkn)[1] == std::string("pin")){
						Variable pin_var_node(token_type, "pin", var_name, std::get<1>(tkn)[2]);
						return pin_var_node;
					}

					//If it's not a pin variable, let's check what's going on in the statement
					std::string statement = std::get<1>(tkn)[1];
					Variable varnode(token_type, "", var_name, statement);
					varnode.type = getTypeOfVar(statement);
				}break;
				
				case TokenType::FUNCTION: {
					int ref = 0;
					int end_scope_pos = -1;



					Function fn();

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
						Error::updateAditionalInfo(std::get<1>(tkn)[0]);
						Logger::Panic( Error::Get("AST001") );
					}else{ //If there is a scope:
						
						//Tell i to skip all tokens inside the scope so we dont add nodes twice
						i = i + ((end_scope_pos-pos) - 1);
						//For all tokens INSIDE the function scope
						for(int k=pos; k < end_scope_pos; k++){
							//Generate & Add the node to our function Node
							Logger::Dev("|r"+std::get<1>(globalTokens[k])[0]);
						}

					}				
					
					//for each sub k until NFinal
					//add GenNode(k)
					//done :)
					
				}

				default:
				break;
			}

			Node a;
			return a;

		}


		//We do recursive scopes here, watch out!
		Node MakeAST(Tokens tkns){
			Logger::Dev("|p(AST) |wStarting AST with " + std::to_string(tkns.size()) + " tokens");
			globalTokens = tkns;

			Node global;

			for(i; i < tkns.size(); i++){
				Token tkn = tkns[i];

				auto nodeToAdd = GenNode(tkns[i], i);
				global.insert(&nodeToAdd);

				Logger::Dev(std::get<1>(tkn)[0]);

			}


			return global;
		}

		// void MakeAST(Tokens tkns){
		// 	Logger::Dev("|p(AST) |wStarting AST with " + std::to_string(tkns.size()) + " tokens");

		// 	Node global;
		// 	Variable node2(TokenType::VAR, "string","my_String","hello");
		// 	global.insert(&node2);
			
		// 	for(int i = 0; i < global.nodes.size(); i++){
				
		// 		auto cn = global.getNode(i);
		// 		Node *PointerToNode = cn;


		// 		if(cn->tokentype == Tokenizer::VAR){
		// 			Logger::Dev("AST: VAR FOUND");
		// 			auto var = dynamic_cast<Variable*>(PointerToNode);
		// 			// std::cout << var->var_name << "\n"; //this will work
		// 		}

		// 	}
		// }

		/*
		
			ADD CLOSING AND OPEN ARROW {} FIRST
		*/

};
