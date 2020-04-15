#pragma once

inline namespace Logger {

    enum WindowsColor {

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

        
        if(PLATFORM_NAME == "windows"){
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
        }
       
    }

    void Log(std::string message){

        for(int i = 0; i < message.size(); i++){

            // If a separator is reached ej: |r
            if(message.at(i) == separator){

                // Change text color of console to apropiate color in this case "r"
                changeColor(&message[i+1]);

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
}
