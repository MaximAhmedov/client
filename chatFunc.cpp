#include "chatFunc.h"

chatFunc::chatFunc(bool & session)
{
    int ipChoice;
    std::string ipLine = "Is the server on this PC? \n\t1 - yes\n\t2 - no\n";
    std::cout << ipLine;
    while(!session){
        inputCommand(ipChoice,ipLine);
        switch(ipChoice){
            case 1:{
                session = start();
                break;
            }
            case 2:{
                std::cout << "input IP:\n";
                char x[16];
                std::cin >> x;
                session = start(x);
                break;
            }
            default:{
                clear_screen();
                std::cout << "Input Error!\n\n";
                break;
            }
        }
    }
}

chatFunc::~chatFunc()
{
    this->serv.stopServer();
}

bool chatFunc::start(const char *x)
{
    return this->serv.startServer(x);
}

bool chatFunc::mainMenu(bool &session)
{
    std::string showMM = "\t1 - Sign in\n \t2 - Registration\n \t3 - Exit\n";
    int choice;
    bool chatCon = false;
    clear_screen();
    std::cout << showMM;
    inputCommand(choice, showMM);
    if(choice == 3){
        std::cout << "end connection";
        session = false;
        return false;
    }

    switch(choice){
        case 1:
        {
            return signIn();
            break;
        }
        case 2:
        {
            return registration();
            break;
        }
        default:
        {
            return false;
            break;
        }
    }
}

void chatFunc::secondMenu()
{
    bool inChatCon = true;
    while(inChatCon){
        isBanned();
        int inChat;
        std::string showSM = "\t1 - All users\n \t2 - My messages\n \t3 - Sign out\n";
        clear_screen();
        std::cout << showSM;
        inputCommand(inChat, showSM);
        if(inChat == 3){
            signOut();
            inChatCon = false;
            break;
        }
        switch(inChat){
            case 1:
            {
                showAllUsers();
                break;
            }
            case 2:
            {
                showAllChats();
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

void chatFunc::isBanned()
{
    std::string cmd = "ISBAN" + delim + this->_login + delim;
    this->serv.sendTo(cmd);
    int x = 0;
    std::string tmp;
    tmp = this->serv.recFrom();
    x = std::stoi(tmp);
    status = x;
    if(status){
        std::cout << "You're banned, close app and go to touch some grass\n";
        system("pause");
        exit (1);
    }
}

bool chatFunc::signIn()
{
    clear_screen();
    std::string tmpPass;
    std::string signcom;
    std::cout << "Enter 0 to return or follow the commands:\nEnter login\n";
    std::cin >> this->_login;
    if (this->_login[0] == '0' && this->_login.size() == 1)
		    return false;
    std::cout << "Enter pasword\n";
    std::cin >> tmpPass;
    if (tmpPass[0] == '0' && tmpPass.size() == 1)
		    return false;
    signcom = "SIGNIN" + delim + this->_login + delim + makePass(tmpPass) + delim;
    this->serv.sendTo(signcom);
    return this->checkAuth(this->serv.recFrom());
}

bool chatFunc::registration()
{
    clear_screen();
    std::string tmpName;
    std::string tmpPass;
    std::string tmpPass2;
    std::string regcom;
    while(true){
        std::cout << "Enter 0 to return or follow the commands:\nEnter name\n";
        std::cin >> tmpName;
        if (tmpName[0] == '0' && tmpName.size() == 1)
		    return false;
        std::cout << "Enter login\n";
        std::cin >> this->_login;
        if (this->_login[0] == '0' && this->_login.size() == 1)
		    return false;
        std::cout << "Enter password\n";
        std::cin >> tmpPass;
        if (tmpPass[0] == '0' && tmpPass.size() == 1)
		    return false;
        std::cout << "Repeat password\n";
        std::cin >> tmpPass2;
        if (tmpPass2[0] == '0' && tmpPass2.size() == 1)
		    return false;
        if(tmpPass == tmpPass2){
            regcom = "REGIS" + delim + this->_login + delim + tmpName + delim + makePass(tmpPass) + delim;
            this->serv.sendTo(regcom);
            return this->checkAuth(this->serv.recFrom());
        }
        else{
            clear_screen();
            std::cout << "Incorrect re-password entry!\n";
        }
    }
}

bool chatFunc::checkAuth(std::string &checkstr)
{
    if(checkstr == "succes")
        return true;
    else{
        std::cout << checkstr << '\n';
        return false;}
}

void chatFunc::chatting(int x)
{
    std::string text;
    std::string friendLogin = userContainer.at(x).first;
    std::cin.ignore();
    while(true){
        clear_screen();
        isBanned();
        std::string tmpstr = "CHATW%" + this->_login + delim + friendLogin + delim;
        this->serv.sendTo(tmpstr);
        text.clear();
        text = this->serv.recFrom();
        if(std::stoi(parsedPart(text))){
            messagesHandling(text);
        }
        std::cout << text << "\nEnter your message and press Enter to send, to return send 0\n";
        text.clear();
        std::getline(std::cin, text, '\n');
        if (text[0] == '0' && text.size() == 1){
            clear_screen();
            break;
        }
        else{
            std::string tmpstr2 = "ADDMES%" +  this->_login + delim + friendLogin + delim + text + delim;
            this->serv.sendTo(tmpstr2);
        }
    }
}

void chatFunc::showAllUsers()
{
    isBanned();
    clear_screen();
    int x = 0;
    std::string tmpstr = "ALLUSER%" + this->_login + delim;
    this->serv.sendTo(tmpstr);
    tmpstr.clear();
    tmpstr = this->serv.recFrom();
    int amountOfUsers = std::stoi(parsedPart(tmpstr));
    if(amountOfUsers >= 1){
        tmpstr = responseHandling(tmpstr);
    }
    tmpstr += "\nSelect a user or enter 0 to return\n";
    while(true){
    std::cout << tmpstr;
    this->inputCommand(x, tmpstr);
    if(x >= 1 && x <= amountOfUsers){
        this->chatting(x);
    }
    else if(x >= 1 && x > amountOfUsers){
        clear_screen();
        std::cout << "Non-existent user number!!!\n";
        continue;
    }
    else
        return;
    }
}

void chatFunc::showAllChats()
{
    isBanned();
    clear_screen();
    int x = 0;
    std::string tmpstr = "ALLCHATS%" + this->_login + delim;
    this->serv.sendTo(tmpstr);
    tmpstr.clear();
    tmpstr = this->serv.recFrom();
    int amountOfChats = std::stoi(parsedPart(tmpstr));
    if(amountOfChats >= 1){
        tmpstr = responseHandling(tmpstr);
    }
    tmpstr += "\nSelect the dialog number or 0 to return\n";
    while(true){
    std::cout << tmpstr;
    this->inputCommand(x, tmpstr);
    if(x >= 1 && x <=amountOfChats){
        this->chatting(x);
    }
    else if(x >= 1 && x > amountOfChats){
        clear_screen();
        std::cout << "Non-existent dialogue number!!!\n";
        continue;
    }
    else
        return;
    }
}

void chatFunc::signOut()
{
    this->_login.clear();
}

int chatFunc::inputCommand(int& x, std::string interfaceLine)
{
    while(!(std::cin >> x))
    {
        clear_screen();
        std::cout << "Incorrect input!!!\n\n";
        std::cout << interfaceLine;
        std::cin.clear();
        std::cin.ignore(max_size, '\n');   
    }
    return x;
}

std::string chatFunc::parsedPart(std::string &stringLine)
{
    std::string parsedPart = stringLine.substr(0,stringLine.find(delim));
	stringLine.erase(0,stringLine.find(delim) + 1);
    return parsedPart;
}

std::string chatFunc::makePass(std::string &pasw)
{
    char tmpArray[LOGINLENGTH];
	std::fill(tmpArray, tmpArray+LOGINLENGTH, '1');
	for(int i = 0; i < pasw.size(); i++){
		tmpArray[i] = pasw[i];
	}
	uint* sh1 = sha1(tmpArray, LOGINLENGTH);
    char out[15];
    std::fill(out, out + sizeof(out), '1');
    for(int i = 0; i < 5; i++){
        snprintf(out+i*3, 4, "%02x ", sh1[i]);
    }
    std::string strPass(out);
    return strPass;
}

std::string chatFunc::responseHandling(std::string &response)
{
    std::string handledResponse;
    userContainer.clear();
    int counter = 1;
    while(true){
        if(response.empty())
            break;
        int x = std::stoi(parsedPart(response));
        std::string login = parsedPart(response);
        std::string name = parsedPart(response);
        logName.first = login;
        logName.second = name;
        userContainer[counter++] = logName;
    }
    
    for(std::map<int, std::pair<std::string,std::string>>::iterator it = userContainer.begin();it != userContainer.end(); ++it){
        handledResponse += std::to_string(it->first) + " " + it->second.first + " | " + it->second.second + "\n";
    }
    return handledResponse;
}

void chatFunc::messagesHandling(std::string &messages)
{
    int counter = std::stoi(parsedPart(messages));
    for(int i = 0; i < counter; i++){
        std::string senderLog = parsedPart(messages);
        std::string time = parsedPart(messages);
        std::string text = parsedPart(messages);


        std::cout << time + " | "; 
        if(senderLog.size()<12){
            std::cout << senderLog << std::string(12 - senderLog.size(), ' ') << " | ";
        }
        else{
            std::cout << senderLog.substr(0,12) << " | ";
        }
        if(text.size() >= 64){
            std::string prevPart;
            while(text.size()>= 64){
                
                prevPart += text.substr(0,63);
                prevPart += "-|\n" + std::string(time.size(),' ') + " | " + std::string(12,' ') + " | ";
                text.erase(0,63);
                if(text[0] == ' '){
                    text.erase(0,1);
                }
            }
            prevPart += text + std::string(64 - text.size(), ' ') + '|';
            text = prevPart;
        }
        else{
            text = text + std::string(64 - text.size(), ' ') + '|';
        }
        std::cout << text << '\n';\
        std::cout << std::string(time.size(),'-') << " + " << std::string(12,'-') << " + " << std::string(64,'-') << "|\n";
        
    }
}


