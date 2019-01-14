//
// Created by david on 1/1/19.
//
#ifndef PROBLEMSOLVER_CLIENTHANDLER_H
#define PROBLEMSOLVER_CLIENTHANDLER_H
#include "CacheManager.h"
#include <string>
#include <map>
#include <vector>

using namespace std;
// The client handler interface defines the behavior of the client hander.
class ClientHandler {
public:
    // Handles the client, string for input file, output file and port.
    virtual void handleClient(vector<string> input,vector<string> output,int port)=0;
    // Returns the cahce manager.
    virtual CacheManager* getClientCache()=0;
};
#endif //PROBLEMSOLVER_CLIENTHANDLER_H

