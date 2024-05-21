#include "client.h"

Client::Client(){
    myServer.startServer();
};
Client::~Client(){
    myServer.stopServer();
};
