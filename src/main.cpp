#include <string>

#include "BusServer.h"
#include "RGBSlave.h"
#include "SlaveManager.h"

int main() {
    BusServer bus_server;
    bus_server.setup("0.0.0.0", 5000);

    SlaveManager& slave_manager_ref = bus_server.getSlaveManager();
    
    slave_manager_ref.createSlave(SensorType::RGB_LED, 0x69);

    bus_server.start();
}