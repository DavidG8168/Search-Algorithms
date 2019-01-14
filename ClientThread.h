#ifndef CLIENTTHREAD_H
#define CLIENTTHREAD_H
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
    // Holds the names of the input files.
    vector<string> nameoffileinput;
    // Holds the names of the output files.
    vector<string> nameoffileoutput;
    // The port.
    int port;
};
#endif //CLIENTTHREAD_H
