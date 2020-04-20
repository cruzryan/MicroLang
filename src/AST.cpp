class AST {
    
    private:

        struct Node {
            
            std::vector<Node*> nodes;

            TokenType tt;

            auto additional_info[];
            
                        
        }

    public:



};



	// struct Node {

    //         std::vector<Node*> nodes;
	// 		//TokenType tt;
	// };

	// //variable 
	// template <typename T>
	// struct Var : Node {

	// 	T value;

	// 	Var(T val){
	// 		value = val;
	// 	}
	
	// };

    
	// std::vector<std::unique_ptr<struct Node>> bruh;
	// bruh.push_back(std::unique_ptr<Var> v(new <int> Var(3)));