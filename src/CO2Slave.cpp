#include "CO2Slave.h"

#include "packets.h"

CO2Slave::CO2Slave(uint8_t id, int i2c_address) : id(id) {
    state_packet.header.ptype = PacketType::DATA;
    state_packet.header.length = sizeof(struct sensor_packet_co2);

    state_packet.data.rgb_light.metadata.sensor_id = id;
    state_packet.data.rgb_light.metadata.sensor_type = SensorType::CO2;
}

const void* CO2Slave::getData() { return &state_packet; }

bool CO2Slave::getStatus() { return false; }

int CO2Slave::getId() { return id; }

void CO2Slave::setData(void* data) {}

void CO2Slave::start(int i2c_fd) {}

void CO2Slave::stop() {}
