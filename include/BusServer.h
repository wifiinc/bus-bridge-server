#pragma once
#include <arpa/inet.h>
#include <sys/socket.h>

#include <string>

#include "SlaveManager.h"
#include "packets.h"

#define BUFFER_SIZE 1024

class BusServer {
   public:
    BusServer() : listening_fd(-1) {}

    /**
     * @brief Setup for the IP socket and the I2C slaves connection
     * @details This method will set up a socket for listening on the network and will also tell the
     * underlying SlaveManager object to initialize its I2C bus
     * @param ip The IP address to listen on within the network
     * @param port The TCP port to listen on
     * @throws std::invalid_argument if the passed IP address or port number are invalid
     * @throws std::runtime_error if the socket creation fails
     */
    void setup(std::string ip, int port);

    /**
     * @brief Open the underlying socket for incoming connections
     * @throws std::runtime_error if the listening fails
     */
    void listen();

    /**
     * @brief Send a sensor packet to a connected network client
     * @details Depending on the data set in the packet header, send a certain amount of data to the
     * client.
     * @param pkt A pointer to the sensor_packet struct to send over
     * @param fd The file descriptor to send the packet over
     * @throws std::runtime_error if the sending fails for any reason
     */
    void send(struct sensor_packet* pkt, int fd);

    /**
     * @brief Start the main loop of the BusServer
     * @details This will first initialize the underlying I2C connections to the
     * directly-connected slave devices, and then start accepting and processing network clients
     */
    void start();

    /**
     * @brief balls
     */
    SlaveManager& getSlaveManager();

   private:
    int listening_fd;

    struct sockaddr_in listening_address;
    bool wemos_bridge_connected = false;
    char buffer[BUFFER_SIZE];

    SlaveManager slave_manager;
};
