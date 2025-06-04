#include <string>

#include "BusServer.h"
#include "RGBSlave.h"
#include "SlaveManager.h"

int main() {
    BusServer bus_server;
    SlaveManager slave_manager;
    sensor_packet_rgb_light packet;
    // packet.metadata.sensor_type = SensorType::RGB_LIGHT;
    // packet.metadata.sensor_id = 0x80;
    packet.red_state = 255;
    packet.green_state = 0;
    packet.blue_state = 100;

    // bus_server.setup("0.0.0.0", 5000);
    // bus_server.start();
    slave_manager.initialize();

    slave_manager.createSlave(SensorType::RGB_LIGHT, 0x80, 0x55);
    BaseSlave* base_slave = slave_manager.getSlave(0x80);
    RGBSlave* rgb_slave = dynamic_cast<RGBSlave*>(base_slave);
    rgb_slave->setData(&packet);
}