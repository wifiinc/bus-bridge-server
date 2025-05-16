#pragma once
#include "WemosClient.h"
#include "SlaveManager.h"
#include "packets.h"
#include <sys/socket.h>

#define BUFFER_SIZE 1024

class BusServer {
    public:
        BusServer() = default;

        void setup(std::string& ip, int port);
        void listen();
        void send(struct sensor_packet*);
    private:
        int listening_fd;
        struct sockaddr_in listening_address;
        bool wemos_bridge_connected = false;
        char buffer[BUFFER_SIZE];
    };