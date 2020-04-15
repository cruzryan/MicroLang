namespace Console {

    //Logger::Log("Running in |rDEBUG_MODE");

    void CheckParameters(int n, char *args[]){
            
	    //If no arguments are passed to the compiler 
	    if(n == 1){

		//Show error and close the program
		Logger::Panic(Error::P0000);

	    }

    }
}