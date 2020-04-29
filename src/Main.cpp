#include <iostream>
#include <fstream>
#include <tuple>
#include <vector>
#include <memory>
#include <regex>

#include "PlatformCheck.cpp"
#include "Logger.cpp"
#include "Error.cpp"
#include "Test.cpp"
#include "Tokenizer.cpp"
#include "AST.cpp"
#include "Assembler.cpp"
#include "Console.cpp"

using namespace std;


int main(int argc, char *argv[]){

	Logger::Log("|bMicroLang |r(Beta)\n");
	Console::CheckParameters(argc,argv);

} 