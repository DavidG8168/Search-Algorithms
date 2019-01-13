//
// Created by david on 1/6/19.
//
#ifndef PROBLEMSOLVER_CLIENTTHREAD_H
#define PROBLEMSOLVER_CLIENTTHREAD_H
#include "ClientHandler.h"
#include <vector>
using namespace std;
// This struct is used to pass parameters to the threads.
struct params {
    int port;
    ClientHandler* c;
};
// The parameters that are passed to the client handler server.
struct parameters {
    vector<string> nameoffileinput;
    vector<string> nameoffileoutput;
    int port;
};
#endif //PROBLEMSOLVER_CLIENTTHREAD_H
