namespace Console {

    const std::string DEV_FILE_PATH = "./tests/variables/assign_variables.micro";

    void CheckParameters(int n, char *args[]){
            

	    //If no arguments are passed to the compiler panic
	    if(n == 1) Logger::Panic(Error::Get("A000"));


        /*
        *           TESTS
        */


        //If "test" is passed as a parameter
        if(args[1] == std::string("test")){

            //if "test" is passed with no args then test all 
            if(n == 2) Test::All();
            
            //if a file path is passed as a parameter
            if(n == 3) Test::Path(args[2]);


        }

        /*
        *           BUILDS
        */

        if(args[1] == std::string("build")){
            ///TO-DO
        }


        /*
        *           DEVELOPER DEBUG
        */

        if(args[1] == std::string("dev")){
            
            Logger::setDevMode();
            Logger::Dev("Started");

            //Open dev file & tokenize
            std::string source = Tokenizer::Load(DEV_FILE_PATH);
            Tokenizer::Tokens tokens = Tokenizer::Tokenize(source);
            
            //Use those tokens and make an AST
            AST::Node* AST = AST::MakeAST(tokens);

            //Use that AST and turn it into valid assembly
            Assembler::MakeAssembly(AST);
        }

    }
}