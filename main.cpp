#include <iostream>
#include "myServer.h"

#if defined(_WIN32)
#define clear_screen() system("cls")
#elif defined(_WIN64)
#define clear_screen() system("cls")
#elif defined(__linux__)
#define clear_screen() system("clear")
#endif

int main(){
    myServer serv;
    std::string* stopSlovo = nullptr;
    std::cout << "wait...\n";
    serv.startServer();
    
    while(1){
        clear_screen();
        serv.recFrom(stopSlovo);
        if(serv.checkEnd())
            break;
        else
            serv.sendTo();
    }
    serv.stopServer();

    return 0;
}