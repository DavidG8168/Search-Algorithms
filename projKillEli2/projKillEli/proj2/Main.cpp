//
// Created by david on 1/6/19.
//
#include "MySerialServer.cpp"
#include "MyClientHandler.cpp"
#include <iostream>

// The boot namespace, used to create another main method.
namespace boot {
    class Main {
    public:
        // The main method
        int main(int argc, char** argv) {
            // Create the serial server.
            server_side::Server* server = new MySerialServer();
            // Create the test client handler.
            ClientHandler* ch = new MyClientHandler();
            // Open the server.
            server->open(stoi(argv[1]), ch);
            vector<string> vector1;
            vector<string> vector2;
            vector1.push_back("matrix.txt");
            vector2.push_back("solutions.txt");
            vector1.push_back("matrix.txt");
            vector2.push_back("solutions.txt");
            vector1.push_back("roytheboy.txt");
            vector2.push_back("solutions.txt");
            ch->handleClient(vector1,vector2,stoi(argv[1]));

        }
    };
}