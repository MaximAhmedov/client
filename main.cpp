#include <iostream>
#include "chatFunc.h"

#if defined(_WIN32)
#define clear_screen() system("cls")
#elif defined(_WIN64)
#define clear_screen() system("cls")
#elif defined(__linux__)
#define clear_screen() system("clear")
#endif

int main(){
    //myServer serv;
    bool session = true;
    
    std::string* stopSlovo = nullptr;
    //serv.startServer();

    //add one more WHILE() ???

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
                std::cout << "Ошибка ввода!\n";
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
                    std::cout << "выход из аккаунта";
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
                        std::cout << "Ошибка ввода!\n";
                        break;
                    }
                }
            }
        }
    }

    return 0;
}