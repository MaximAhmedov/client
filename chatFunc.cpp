#pragma once
#include "chatFunc.h"

void chatFunc::showMainMenu(int& x)
{
    std::cout << "\t1 - Войти\n \t2 - Регистрация\n \t3 - Выход\n";
    std::cin >> x;
}

void chatFunc::signIn(std::string& signcom)
{
    std::string tmpLogin;
    std::string tmpPass;
    //this->_login...
    std::cout << "Введите логин\n";
    std::cin >> tmpLogin;
    std::cout << "Введите пароль\n";
    std::cin >> tmpPass;
    signcom = "SIGNIN%" + tmpLogin + '%' + tmpPass + '%';

}

void chatFunc::registration(std::string &regcom)
{
    std::string tmpName;
    std::string tmpLogin;
    std::string tmpPass;
    std::string tmpPass2;

    std::cout << "Введите Имя\n";
    std::cin >> tmpName;
    std::cout << "Введите логин\n";
    std::cin >> tmpLogin;
    std::cout << "Введите пароль\n";
    std::cin >> tmpPass;
    std::cout << "Повторите пароль\n";
    std::cin >> tmpPass2;
    regcom = "REGIS%" + tmpName + '%' + tmpLogin + '%' + tmpPass + '%' + tmpPass2 + '%';
}

bool chatFunc::checkAuth(std::string &checkstr)
{
    // написать код сравнения возращенной строки с true или false
    if(checkstr == "succes")
        return true;
    else
        std::cout << checkstr << '\n';
        return false;
}

void chatFunc::showSecondMenu(int& x)
{
    std::cout << "\t1 - Все пользователи\n \t2 - Мои Сообщения\n \t3 - Выход из аккаунта\n";
    std::cin >> x;
}

void chatFunc::showAllUsers()
{
    // показ всех пользователей
    // выбор пользователя(открывается диалог в котором видно старые смс) или выход(возварт на предю экр)
    // диалог: написание и отправка сообщения, при этом сразу возврат обновленного диалога, с возможностью повторного набора смс
    // или выход ко всем пользователям
}

void chatFunc::showAllChats()
{
    // показ всех диалогов...
}
