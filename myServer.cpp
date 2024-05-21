#include "myServer.h"

myServer::myServer(){};
myServer::~myServer(){

};
void myServer::startServer(){
    WIN(WSADATA wsaData;);
    WIN(iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if(iResult != 0){
        std::cout << "WSAStartup failed: " << iResult << std::endl;
    }
    else
        std::cout << "WSAStartup is ok" << std::endl;);
  
    ClientSocket = socket(AF_INET,SOCK_STREAM,0);
    if(ClientSocket == INVALID_SOCKET){
        std::cout << "error at socket():" << WSAGetLastError() << std::endl;
        WIN(WSACleanup());
    }
    else
        std::cout << "socket() is ok" << std::endl;

    serveraddress.sin_family = AF_INET;
    serveraddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    serveraddress.sin_port = htons(PORT);

    iResult = connect(ClientSocket,(struct sockaddr*)&serveraddress, sizeof(serveraddress));
    if(iResult==SOCKET_ERROR){
        std::cout << "connect error" << std::endl;
        WIN(closesocket(ClientSocket))NIX(close(ClientSocket));
        WIN(WSACleanup());
    }
    else
        std::cout << "connect is ok" << std::endl;

    if(ClientSocket == INVALID_SOCKET){
        std::cout << "unable to connect to server" << std::endl;
        WIN(WSACleanup());
    }
    else
        std::cout << "connected to the server" << std::endl;
};

void myServer::recFrom(std::string* stopSlovo){
    bzero(recvBuff, recvBuffLen);
    message.clear();
    recv(ClientSocket,recvBuff,recvBuffLen,0);
    message = recvBuff;
    if(message == "end connection"){
        this->stopSlovo = true;
        return;
    }
    std::cout << message << std::endl;
};

void myServer::sendTo(){
    bzero(recvBuff, recvBuffLen);
    message.clear();
    std::getline(std::cin, message, '\n');
    send(ClientSocket,message.c_str(),message.length(),0);
};

void myServer::stopServer(){
    shutdown(ClientSocket, 1);
    WIN(closesocket(ClientSocket))NIX(close(ClientSocket));
    WIN(WSACleanup());
};

bool myServer::checkEnd(){
    return stopSlovo;
};