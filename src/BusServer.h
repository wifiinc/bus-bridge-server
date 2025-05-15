#pragma once
#include "WemosClient.h"
#include "SlaveManager.h"

#define BUFFER_SIZE 1024

class BusServer {
private:
    int client_fd;
    int opt;
    char buffer[BUFFER_SIZE];
    WemosClient wemos_client;
};