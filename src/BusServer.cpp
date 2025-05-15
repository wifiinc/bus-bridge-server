#include "BusServer.h"
#include <sys/socket.h>
#include <stdexcept>
#include <arpa/inet.h>
#include <cstring>

BusServer::BusServer(){}

void BusServer::setup(std::string& ip, int port){
    memset(&listening_address, 0, sizeof(listening_address));
    
    if (port <= 0 || port > 65535) {
        throw std::invalid_argument("invalid port passed");
    }

    if (0 == inet_aton(ip.c_str(), &listening_address.sin_addr)) {
        perror("inet_aton()");
        throw std::invalid_argument("invalid IP address passed");
    }

    listening_address.sin_family = AF_INET;
    listening_address.sin_port = htons(port);
}

void BusServer::listen(){
    listening_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == listening_fd){
        perror("socket()");
        throw std::runtime_error("failed to create socket");
    }

    socklen_t len = sizeof(listening_address);

    if (-1 == bind(listening_fd, (struct sockaddr*)&listening_address, len)) {
        perror("bind()");
        throw std::runtime_error("failed to bind socket");
    }
    if(-1 == ::listen(listening_fd, 8)){
        perror("listen()");
        throw std::runtime_error("failed to listen on socket");
    }
}

void BusServer::send(struct sensor_packet* packet_ptr){
    if (!wemos_bridge_connected){
        throw std::runtime_error("no longer connected to socket");
    }
    if(-1 == ::send(listening_fd, packet_ptr, sizeof(struct sensor_header) + packet_ptr->header.length, 0)){
        perror("send()");
        throw std::runtime_error("failed to send on socket");
    }
}