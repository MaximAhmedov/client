#include <iostream>
#include "chatFunc.h"

#if defined(_WIN32)
#define clear_screen() system("cls")
#elif defined(_WIN64)
#define clear_screen() system("cls")
#elif defined(__linux__)
#define clear_screen() system("clear")
#endif

#define WIN(exp) exp
#define NIX(exp)

int main(){
    //setlocale(LC_ALL,"Russian");
    // SetConsoleCP(1251);
    // SetConsoleOutputCP(1251);
    //SetConsoleCP(CP_UTF8);
    //SetConsoleOutputCP(CP_UTF8);

    bool session = false;
    chatFunc chat(session);

    while(session){
        bool chatCon = chat.mainMenu(session);
        if(chatCon){
            chat.secondMenu();
        }
    }

    return 0;
}