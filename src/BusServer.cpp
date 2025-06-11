#include "BusServer.h"

#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cerrno>
#include <cstring>
#include <stdexcept>

#include "RGBSlave.h"
#include "packets.h"
#include "wiringPi.h"
#include "wiringPiI2C.h"

#define RGB_SLAVE_ADDRESS 0x69

void BusServer::setup(std::string ip, int port) {
    // slave_manager.initialize();

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

    listening_fd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
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
    listen();

    int the_fd = -1;

    while (true) {
        char buffer[32] = {0};
        bool net_request = false;

        int new_fd = -1;

        {
            struct sockaddr_in client_address = {0};
            socklen_t client_address_length = sizeof(client_address);

            new_fd = accept4(listening_fd, (struct sockaddr*)&client_address,
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
            } else {
                the_fd = new_fd;
                // printf("new fd: %d\nthe fd: %d\n", new_fd, the_fd);
            }

            if (the_fd != -1) {
                int err;
                int recvd = recv(the_fd, buffer, sizeof(buffer), SOCK_NONBLOCK);
                if (0 == recvd) {
                    close(the_fd);
                    the_fd = -1;
                    continue;
                }

                if (-1 == recvd) err = errno;
                // printf("%d\n", err);
                // perror("recv balls");
                if (-1 == recvd && err != EAGAIN) {
                    perror("recv()");
                    usleep(100000);
                    throw std::runtime_error("reading from client socket failed for some reason");
                } else if (errno != EAGAIN) {
                    // printf("%d\n", recvd);
                } else {
                    // printf("%d\n", recvd);
                    if (recvd > 0) net_request = true;

                    // perror("recv()[1]");
                    usleep(100000);
                }
            }
        }

        if (net_request) {
            struct sensor_packet* pkt_ptr = (struct sensor_packet*)buffer;
            BaseSlave* the_slave = slave_manager.getSlave(pkt_ptr->data.generic.metadata.sensor_id);
            SensorType the_sensor_type = pkt_ptr->data.generic.metadata.sensor_type;
            uint8_t values[8] = {0};

            switch (pkt_ptr->header.ptype) {
                case PacketType::DASHBOARD_POST:
                    switch (the_sensor_type) {
                        case SensorType::LIGHT:
                            values[0] = pkt_ptr->data.light.target_state;

                            the_slave->setData(values);
                            break;

                        case SensorType::RGB_LIGHT:
                            struct RGBData rgb_data = {.R = pkt_ptr->data.rgb_light.red_state,
                                                       .G = pkt_ptr->data.rgb_light.green_state,
                                                       .B = pkt_ptr->data.rgb_light.blue_state};

                            the_slave->setData(&rgb_data);

                            break;
                    }
                    break;

                case PacketType::DASHBOARD_GET:
                    struct sensor_packet state_ptr;
                    memcpy(&state_ptr, the_slave->getData(), sizeof(struct sensor_packet));

                    state_ptr.header.ptype = PacketType::DASHBOARD_RESPONSE;

                    send(&state_ptr, new_fd);
                    break;
            }
        }
    }
}

SlaveManager& BusServer::getSlaveManager() { return slave_manager; }
