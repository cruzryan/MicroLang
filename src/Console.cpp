namespace Console {

    const std::string DEV_FILE_PATH = "../tests/variables/assign_variables.micro";

    void CheckParameters(int n, char *args[]){
            

	    //If no arguments are passed to the compiler panic
	    if(n == 1) Logger::Panic(Error::A000);


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
            Tokenizer::Load(DEV_FILE_PATH);
            
        }

    }
}