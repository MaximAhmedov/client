#pragma once
#include <iostream>
#include <string.h>



class chatFunc{
public:
    chatFunc();
    ~chatFunc();

    void showMainMenu(int& x);
    void signIn(std::string& signcom);
    void registration(std::string& regcom);
    bool checkAuth(std::string& checkstr);
    //void closeProg();
    void showSecondMenu(int& x);
    void showAllUsers(); // прописать код для чаттинга
    void showAllChats(); // прописать код для чаттинга
    //void signOut();

    std::string makeCommand();
private:
    std::string _login;



};