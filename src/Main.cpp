#include <iostream>
#include <fstream>
#include <tuple>
#include <vector>

#include "PlatformCheck.cpp"
#include "Logger.cpp"
#include "Error.cpp"
#include "Test.cpp"
#include "Tokenizer.cpp"
#include "Console.cpp"

using namespace std;

int main(int argc, char *argv[]){

	Logger::Log("|bMicroLang |r(Beta)\n");
	Console::CheckParameters(argc,argv);

} 