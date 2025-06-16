#include <string>

#include "BusServer.h"
#include "RGBSlave.h"
#include "SlaveManager.h"

int main() {
    BusServer bus_server;
    bus_server.setup("0.0.0.0", 5000);

    SlaveManager& slave_manager_ref = bus_server.getSlaveManager();

    {
        int fd = wiringPiI2CSetup(0x69);

        slave_manager_ref.createSlave(SensorType::RGB_LIGHT, 0x69);
        slave_manager_ref.getSlave(0x69)->start(fd);
    }

    bus_server.start();
}
