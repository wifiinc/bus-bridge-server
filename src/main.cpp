#include "BusServer.h"
#include <string>

int main() {
    BusServer bus_server;

    bus_server.setup("0.0.0.0", 5000);
    bus_server.start();
}
