#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include "Solver.h"
#include "CacheManager.h"
#include "ClientThread.h"
#include "ClientHandler.h"
#include "FileCacheManager.cpp"
#include "MatrixProblem.cpp"
#include "GlobalCache.h"
// Handles the client with their stupid problem.
class  MyClientHandler: public ClientHandler {
public:
    // Connects to the server and handles the problem.
    void handleClient(vector<string> input, vector<string> output, int port) {
        //create a matrix
        MatrixProblem *q = new MatrixProblem();
        // Iterate the input files.
        for(int i=0;i<input.size();i++){
            q->GetInitialState(input[i].c_str());
            string problem = q->makeProblem();
            // If the solution exists in the cache, write from it to the output file.
            if (globalcache->getSolution(problem) != "None") {
                ofstream newFile(output[i], std::ios_base::app);
                // Remove resolved problems from the lists.
                input.erase(input.begin() + i);
                output.erase(output.begin() + i);
                // Write solutions.
                if (newFile.is_open()) {
                    newFile << globalcache->getSolution(problem) << "\n";
                } else {
                    perror("Error opening file.");
                }
                newFile.close();
            }
            // Load the struct.
            parameters *p = new parameters();
            p->port=port;
            p->nameoffileinput=input;
            p->nameoffileoutput=output;
            // Create the thread.
            pthread_t pthread;
            pthread_create(&pthread, nullptr, this->conectclient, p);
            pthread_join(pthread, nullptr);
        }
    }
    // Get the current cache.
    CacheManager* getClientCache() {
        return globalcache;
    }
    // Open the server and read the data from it into a buffer.
    // Code taken from the Moodle example.
    static void * conectclient(void * args) {
        //here we are goinmg to iterate all the path map
        int port = ((parameters *) args)->port;
        vector<string>  nameoffileinput = ((parameters *) args)->nameoffileinput;
        vector<string>  nameoffileoutput = ((parameters *) args)->nameoffileoutput;
        int sockfd, portno, n;
        struct sockaddr_in serv_addr;
        struct hostent *server;
        char buffer[1024];
        portno = port;
        /* Create a socket point */
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0) {
            perror("ERROR opening socket");
            exit(1);
        }
        server = gethostbyname("127.0.0.1");
        if (server == NULL) {
            fprintf(stderr,"ERROR, no such host\n");
            exit(0);
        }
        bzero((char *) &serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
        serv_addr.sin_port = htons(portno);
        /* Now connect to the server */
        if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
            perror("ERROR connecting");
            exit(1);
        }
        /* Now ask for a message from the user, this message
           * will be read by server
        */
        bzero(buffer,1024);
        // Moosh the file names together to send them to the server.
        string bigstr="";
        for(int i=0;i<nameoffileinput.size();i++){
            bigstr=bigstr+nameoffileinput[i]+","+nameoffileoutput[i];
            if(i!= nameoffileinput.size() - 1) {
                bigstr = bigstr+",";
            }
        }        strcpy(buffer,bigstr.c_str());
        /* Send message to the server */
        n = write(sockfd, buffer, strlen(buffer));
        if (n < 0) {
            perror("ERROR writing to socket");
            exit(1);
        }
        /* Now read server response */
        bzero(buffer,1024);
        n = read(sockfd, buffer, 1023);
        if (n < 0) {
            perror("ERROR reading from socket");
            exit(1);
        }
        printf("%s\n",buffer);
        return 0;
    }
};