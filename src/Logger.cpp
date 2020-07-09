#pragma once
#include <iostream>

inline namespace Logger {

    bool dev_mode = false;

    enum class WindowsColor {

        WHITE = 0x0F,
        RED = 0x0C,
        GREEN = 0x0A,
        BLUE = 0x09,
        YELLOW = 0x0E,
        PURPLE = 0x0D,
        GREY = 0x08

    };

    const char& separator = '|';

    /*
        Color codes: 

        &w = white
        &r = red
        &g = green
        &b = blue
        &y = yellow
        &p = purple
        &k = grey

    */

    void changeColor(const char* c){


        #if defined(_WIN32) || defined(_WIN64)
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

            switch(c[0]){
                case 'w':
                    SetConsoleTextAttribute(hConsole, WindowsColor::WHITE);
                break;
                case 'r':
                    SetConsoleTextAttribute(hConsole, WindowsColor::RED);
                break;
                case 'g':
                    SetConsoleTextAttribute(hConsole, WindowsColor::GREEN);
                break;
                case 'b':
                    SetConsoleTextAttribute(hConsole, WindowsColor::BLUE);
                break;
                case 'y':
                    SetConsoleTextAttribute(hConsole, WindowsColor::YELLOW);
                break;
                case 'p':
                    SetConsoleTextAttribute(hConsole, WindowsColor::PURPLE);
                break;
                case 'k':
                    SetConsoleTextAttribute(hConsole, WindowsColor::GREY);
                break;
            }
        #elif defined(__linux__)

        switch(c[0]){
                case 'w':
                    std::cout << "\033[1;" << "97" << "m";
                break;
                case 'r':
                    std::cout << "\033[1;" << "31" << "m";
                break;
                case 'g':
                    std::cout << "\033[1;" << "92" << "m";
                break;
                case 'b':
                    std::cout << "\033[1;" << "34" << "m";
                break;
                case 'y':
                    std::cout << "\033[1;" << "33" << "m";
                break;
                case 'p':
                    std::cout << "\033[1;" << "35" << "m";
                break;
                case 'k':
                    std::cout << "\033[1;" << "90" << "m";
                break;
            }
        #endif
    }

    void Log(std::string message){

        for(int i = 0; i < message.size(); i++){

            // If a separator is reached ej: |r
            if(message.at(i) == separator){

                // Change text color of console to apropiate color in this case "r"
                if(message[i+1] != (char)'|'){ // Don't change color when you encounter ||
                    changeColor(&message[i+1]);
                }else{
                    std::cout << message.at(i);
                }

                //Skip the next char
                i = i + 1;

            }else{
                std::cout << message.at(i);
            }
        }       

        //Reset color to default, we're using white as default
        changeColor("w");
        std::cout << "" << std::endl;
    
    }

    //Useful for handling errors
    void Panic(std::string message){
        Log(message);
        exit(0);
    }

    void setDevMode(){ 
        dev_mode = true;
    } 

    //What we log when we're in Dev Mode
    void Dev(std::string message){
        if(dev_mode){
            Log("|b(Dev Mode)|w " + message);
        }
    }  
}
