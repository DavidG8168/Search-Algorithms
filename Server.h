#ifndef SERVER_H
#define SERVER_H
#include "ClientHandler.h"
// The server namespace.
namespace server_side {
    class Server {
    public:
        // Opens the server.
        virtual void open(int port, ClientHandler *c) = 0;
        // Stops the server.
        virtual void stop(int sockfd)=0;
    };
}
#endif //SERVER_H
