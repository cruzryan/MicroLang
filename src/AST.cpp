namespace AST {

		using namespace Tokenizer; //To access Tokens & Token type defintions

        struct Node {
            std::vector<Node*> nodes;
          //  TokenType tt;
        };

		struct Function : Node {
			std::vector<std::string> params;
		};

		struct Variable : Node {
			std::string type;
			std::string var_name;
			std::string value;
		};

		struct If : Node {
			std::string statement;
			Node* else_node; //if there is no else, else_node will be NULL
		};

		void MakeAST(Tokens tkns){
			Logger::Dev("|p(AST) |wStarting AST with " + std::to_string(tkns.size()) + " tokens");
		}

};
