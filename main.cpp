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
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    bool session = true;

    while(session){
        chatFunc chat;
        std::string stringLine = chat.showMainMenu();
        int choice;
        bool chatCon = false;
        clear_screen();
        std::cout << stringLine;
        chat.inputCommand(choice, stringLine);
        if(choice == 3){
            std::cout << "end connection";
            session = false;
            break;
        }

        switch(choice){
            case 1:
            {
                 chatCon = chat.signIn();
                 break;
            }
            case 2:
            {
                chatCon = chat.registration();
                break;
            }
            default:
            {
                std::cout << "Input Error!\n";
                break;
            }
        }
        
        if(chatCon){
            bool inChatCon = true;
            while(inChatCon){
                int inChat;
                clear_screen();
                stringLine = chat.showSecondMenu();
                std::cout << stringLine;
                chat.inputCommand(inChat, stringLine);
                if(inChat == 3){
                    std::cout << "Logout";
                    chat.signOut();
                    inChatCon = false;
                    break;
                }
                switch(inChat){
                    case 1:
                    {
                        chat.showAllUsers();
                        break;
                    }
                    case 2:
                    {
                        chat.showAllChats();
                        break;
                    }
                    default:
                    {
                        std::cout << "Input Error!\n";
                        break;
                    }
                }
            }
        }
    }

    return 0;
}