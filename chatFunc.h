#pragma once
#include <iostream>
#include <string.h>
#include <limits>
#include "myServer.h"
#include "Sha1.h"
#include<map>

#define LOGINLENGTH 10

#if defined(_WIN32)
#define clear_screen() system("cls")
#elif defined(_WIN64)
#define clear_screen() system("cls")
#elif defined(__linux__)
#define clear_screen() system("clear")
#endif

constexpr auto max_size = std::numeric_limits<std::streamsize>::max();

class chatFunc{
public:
    chatFunc(bool & session);
    ~chatFunc();
    bool start(const char *x = "127.0.0.1");
    bool mainMenu(bool & session);
    void secondMenu();
    bool signIn();
    bool registration();
    bool checkAuth(std::string& checkstr);
    void chatting(int x);
    void showAllUsers();
    void showAllChats();
    void signOut();
    int inputCommand(int& x, std::string interfaceLine);
    std::string parsedPart(std::string& stringLine);
    std::string makePass(std::string& pasw);
    std::string responseHandling(std::string& response);
    void messagesHandling(std::string& messages);
private:
    std::pair<std::string,std::string> logName;
    std::map<int, std::pair<std::string,std::string>> userContainer;
    myServer serv;
    std::string _login;
    std::string delim = "%";
};