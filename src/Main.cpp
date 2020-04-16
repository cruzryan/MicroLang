#include <iostream>
#include <fstream>

#define DEVMODE false

#include "PlatformCheck.cpp"
#include "Logger.cpp"
#include "Error.cpp"
#include "Test.cpp"
#include "Console.cpp"

//#include "Parser.cpp"

using namespace std;

int main(int argc, char *argv[]){

	Logger::Log("|bMicroLang |r(Beta)\n");
	Console::CheckParameters(argc,argv);

} 