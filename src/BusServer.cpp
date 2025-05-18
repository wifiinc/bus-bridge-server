#include "BusServer.h"

#include <arpa/inet.h>
#include <sys/socket.h>

#include <cerrno>
#include <cstring>
#include <stdexcept>

#include "packets.h"
#include "wiringPi.h"
#include "wiringPiI2C.h"

void BusServer::setup(std::string ip, int port) {
    slave_manager.initialize();

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

    listening_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == listening_fd) {
        perror("socket()");
        throw std::runtime_error("failed to create socket");
    }

    {
        int one = 1;
        if (-1 ==
            setsockopt(listening_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &one, sizeof(one))) {
            perror("setsockopt()");
            throw std::runtime_error("failed to set socket options");
        }
    }

    socklen_t len = sizeof(listening_address);

    if (-1 == bind(listening_fd, (struct sockaddr*)&listening_address, len)) {
        perror("bind()");
        throw std::runtime_error("failed to bind socket");
    }
}

void BusServer::listen() {
    if (-1 == ::listen(listening_fd, 8)) {
        perror("listen()");
        throw std::runtime_error("failed to listen on socket");
    }
}

void BusServer::send(struct sensor_packet* packet_ptr, int fd) {
    if (!wemos_bridge_connected) {
        throw std::runtime_error("no longer connected to socket");
    }
    if (-1 == ::send(fd, packet_ptr, sizeof(struct sensor_header) + packet_ptr->header.length, 0)) {
        perror("send()");
        throw std::runtime_error("failed to send on socket");
    }
}

void BusServer::start() {
    // start off by mapping pre-known addresses to ID's
    slave_manager.createSlave(SensorType::RGB_LIGHT, 8, 0x42 /* change to actual ID */);

    listen();

    while (true) {
        {
            struct sockaddr_in client_address = {0};
            socklen_t client_address_length;

            int new_fd = accept4(listening_fd, (struct sockaddr*)&client_address,
                                 &client_address_length, SOCK_NONBLOCK);

            if (-1 == new_fd) {
                int err = errno;
                switch (err) {
                    case EWOULDBLOCK:
                        // no client has tried to connect; no big deal
                        break;

                    default:
                        perror("accept4()");
                        throw std::runtime_error("accept4() failed");
                        break;
                }
            }
        }

        {
            /*
             * more slave_manager stuff here
             */
        }
    }
}
