#include <iostream>
#include "myServer.h"
#include "chatFunc.h"

#if defined(_WIN32)
#define clear_screen() system("cls")
#elif defined(_WIN64)
#define clear_screen() system("cls")
#elif defined(__linux__)
#define clear_screen() system("clear")
#endif

int main(){
    myServer serv;
    bool session = true;
    bool chatCon = false;
    std::string* stopSlovo = nullptr;
    std::string cmdstr;
    serv.startServer();

    //add one more WHILE() ???

    while(session){
        chatFunc chat;
        int choice;
        chat.showMainMenu(choice);

        if(choice == 3){
            std::cout << "end connection";
            session = false;
            break;
        }

        switch(choice){
            case 1:
            {
                chat.signIn(cmdstr);
                serv.sendTo(cmdstr);
                chatCon = chat.checkAuth(serv.recFrom(stopSlovo));
            }
            case 2:
            {
                chat.registration(cmdstr);
                serv.sendTo(cmdstr);
                chatCon = chat.checkAuth(serv.recFrom(stopSlovo));
            }
            default:
            {
                std::cout << "Ошибка ввода!\n";
                //break;
            }
        }
        
        if(chatCon){
            bool inChatCon = true;
            while(inChatCon){
                int inChat;
                chat.showSecondMenu(inChat);
                if(inChat == 3){
                    std::cout << "выход из аккаунта";
                    inChatCon = false;
                    break;
                }
                switch(inChat){
                    case 1:
                    {
                        chat.showAllUsers();
                    }
                    case 2:
                    {
                        chat.showAllChats();
                    }
                }


            }
        }

        // while(1){
        //     clear_screen();
        //     serv.recFrom(stopSlovo);
        //     if(serv.checkEnd())
        //         break;
        //     else
        //         serv.sendTo();
        // }

    }
    serv.stopServer();

    return 0;
}