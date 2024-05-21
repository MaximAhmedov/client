#pragma once
#include <iostream>
#include "myServer.h"

class Client{
public:
Client();
~Client();
void sendReq(std::string& text);
void getData();
private:
myServer myServer;
};