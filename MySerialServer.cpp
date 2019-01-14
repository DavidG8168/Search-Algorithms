//
// Created by david on 1/1/19.
//
#include <iostream>
#include "Server.h"
#include <pthread.h>
#include <thread>
#include "ClientThread.h"
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include "SolutionCreator.cpp"
// Connects the clients one after another to solve their problems,
class MySerialServer: public server_side::Server{
public:
    // Creates the server and runs it, solving the problems of the client stated in the buffer.
    static void* createServer(void* args) {
        // The parameters of the server, port and client handler.
        int port = ((params *) args)->port;
        ClientHandler* c = ((params *) args)->c;
        int sockfd, newsockfd, portno, clilen;
        char buffer[1024];
        struct sockaddr_in serv_addr, cli_addr;
        int  n;
        /* First call to socket() function */
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0) {
            perror("ERROR opening socket");
            exit(1);
        }
        /* Initialize socket structure */
        bzero((char *) &serv_addr, sizeof(serv_addr));
        portno = port;
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = INADDR_ANY;
        serv_addr.sin_port = htons(portno);
        /* Now bind the host address using bind() call.*/
        if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
            perror("ERROR on binding");
            exit(1);
        }
        /* Now start listening for the clients, here process will
           * go in sleep mode and will wait for the incoming connection
        */
        listen(sockfd,5);
        clilen = sizeof(cli_addr);
        /* Accept actual connection from the client */
        newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, (socklen_t*)&clilen);
        if (newsockfd < 0) {
            perror("ERROR on accept");
            exit(1);
        }
        /* If connection is established then start communicating */
        bzero(buffer,1024);
        n = read( newsockfd,buffer,1023 );
        // Solve the problems.
        SolutionCreator* sol = new SolutionCreator();
        sol->solve(buffer);
        if (n < 0) {
            perror("ERROR reading from socket");
            exit(1);
        }
        /* Write a response to the client */
        n = write(newsockfd,"I got your message",18);
        if (n < 0) {
            perror("ERROR writing to socket");
            exit(1);
        }
        return 0;
    }
    // Function opens the server using a struct of parameters sent to a static function.
    void open(int port, ClientHandler *c) {
        params *p = new params();
        p->c = c;
        p->port = port;
        pthread_t pthread;
        pthread_create(&pthread, nullptr, this->createServer, p);
        pthread_detach(pthread);
        // pthread_join(pthread, nullptr);
    }
    // Function used to manually close the socket if needed.
    void stop(int sockfd) {
        close(sockfd);
    }
};