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
		};

		struct Variable : Node {
			std::string type;
			std::string var_name;
			std::string value;
			
			Variable(Tokenizer::TokenType tt, std::string t, std::string vn, std::string v){
				this->type = t;
				this->var_name = vn;
				this->value = v;
				this->tokentype = tt;
			}
		};

		struct If : Node {
			std::string statement;
			Node* else_node; //if there is no else, else_node will be NULL
		};

		Tokens globalTokens;

		//We do recursive scopes here, watch out!
		Node MakeAST(Tokens tkns){
			Logger::Dev("|p(AST) |wStarting AST with " + std::to_string(tkns.size()) + " tokens");
			globalTokens = tkns;

			Node global;

			for(int i = 0; i < tkns.size(); i++){
				Token tkn = tkns[i];

				Logger::Dev(std::get<1>(tkn)[0]);

			}


			return global;
		}


		Node GenNode(Token tkn, int pos){
			
			//Remember, nodes are just tuples, where the first parameter in the tuple is the TokenType
			switch(std::get<0>(tkn)){

				case TokenType::VAR:
					Logger::Dev("|rBRUH THIS IS A VARIABLE XD");
				break;
				default:
				break;
			}

			Node a;

			return a;

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
