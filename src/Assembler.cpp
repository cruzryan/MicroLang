//The assembler turns AST into Assembly the PIC can understand

namespace Assembler {

	using namespace Tokenizer;
    using AST::Node;
	using std::vector;

    /*This is to make sure the user doesn't create the 
    same variable name, or same function name twice*/
    vector<std::string> variableNamesGenerated;
    vector<std::string> functionNamesGenerated;

    void generateVariable(Node* node);

    void nodeAction(Node* node){
        auto nodeType = node->tokentype;
        
        switch(nodeType){
            case TokenType::VAR:
                generateVariable(node);
            break;
        }

    }

    void generateVariable(Node* node){
        std::string var_value;

        // if(node->type == "bool"){
        //     if(node->value == "true") var_value = "11111111";
        //     else var_value = "00000000";
        // }

        // if(node->type == "string"){
        //     //TO-DO
        // }

        


    }

    void parseTheTree(Node* node){
        for(int n = 0; n < node->getNumberOfNodes(); n++){
            auto tempNode = node->getNode(n);

        }
    }

    void MakeAssembly(Node* root){
        Logger::Dev("|r(ASM) |wStarting assembler");
    }

}