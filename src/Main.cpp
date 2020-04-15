#include <iostream>
#include <fstream>
#include "PlatformCheck.cpp"
#include "Logger.cpp"
#include "Error.cpp"
#include "Console.cpp"

//#include "Parser.cpp"

using namespace std;

const bool DEBUG_MODE = true;

int main(int argc, char *argv[]){

	Logger::Log("|bMicroLang |r(Beta)\n");

	Console::CheckParameters(argc,argv);

}