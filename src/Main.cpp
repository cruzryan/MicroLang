#include <iostream>
#include <fstream>
#include "PlatformCheck.cpp"
#include "Logger.cpp"
//#include "Parser.cpp"
//#include "Error.cpp"

using namespace std;

const bool DEBUG_MODE = true;

int main(int argc, char *argv[]){
	
	if (DEBUG_MODE){

		Logger::Log("Running in |rDEBUG_MODE");
		Logger::Log("|kP0001 |rERROR: |wexpected |r; |win Main.micro|y line 32");


	}else{

	
	}

}