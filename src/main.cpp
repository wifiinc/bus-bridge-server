#include <string>

#include "packets.h"
#include "BusServer.h"
#include "SlaveManager.h"
#include "RGBSlave.h"

int main() {
    BusServer bus_server;
    SlaveManager slave_manager;
    sensor_packet_rgb_light packet;
    packet.metadata.sensor_type = SensorType::RGB_LIGHT;
    packet.metadata.sensor_id = 0x80;
    packet.red_state = 255;
    packet.green_state = 0;
    packet.blue_state = 100;

    bus_server.setup("0.0.0.0", 5000);
    bus_server.start();
    slave_manager.createSlave(RGB_LIGHT, 0x80, 0x55);
    RGBSlave rgb_slave = slave_manager.getSlave(0x80);
    rgb_slave.setData(&packet);
}