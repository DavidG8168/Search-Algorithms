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
            // Add all the files with the graphs to the vector.
            // All solutions will go to the solutions text file.
            vector1.push_back("graph1.txt");
            vector2.push_back("solutions.txt");
            vector1.push_back("graph2.txt");
            vector2.push_back("solutions.txt");
            vector1.push_back("graph3.txt");
            vector2.push_back("solutions.txt");
            vector1.push_back("graph4.txt");
            vector2.push_back("solutions.txt");
            vector1.push_back("graph5.txt");
            vector2.push_back("solutions.txt");
            vector1.push_back("graph6.txt");
            vector2.push_back("solutions.txt");
            vector1.push_back("graph7.txt");
            vector2.push_back("solutions.txt");
            vector1.push_back("graph8.txt");
            vector2.push_back("solutions.txt");
            vector1.push_back("graph9.txt");
            vector2.push_back("solutions.txt");
            vector1.push_back("graph10.txt");
            vector2.push_back("solutions.txt");
            // Handle the client.
            ch->handleClient(vector1,vector2,stoi(argv[1]));
        }
    };
}