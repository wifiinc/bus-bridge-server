#pragma once
#include <string>
#include <thread>
#include <netinet/in.h>

struct DataReceiveReturn {
    uint8_t* data;
    size_t length;
};

class WemosClient {
public:
    WemosClient(std::string ip, int port);
    ~WemosClient();

    bool connect();
    void start();
    void disconnect();
    void send(uint8_t* data, size_t length);
    DataReceiveReturn receive();

private:
    int port;
    int buffer_size;
    int hub_port;
    int server_fd;
    struct sockaddr_in address;
    std::thread receive_thread;
    std::string hub_ip;

    void receiveLoop();
};