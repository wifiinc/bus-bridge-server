#include "LightSlave.h"

#include <stdio.h>

#include "packets.h"

LightSlave::LightSlave(uint8_t id, uint8_t i2c_address) : id(id), i2c_address(i2c_address) {
    state_packet.header.ptype = PacketType::DATA;
    state_packet.header.length = sizeof(struct sensor_packet_light);

    state_packet.data.light.metadata.sensor_id = id;
    state_packet.data.light.metadata.sensor_type = SensorType::LIGHT;
}

const void* LightSlave::getData() {
    uint8_t value = wiringPiI2CRead(fd);

    state_packet.data.light.target_state = value;

    return &state_packet;
}

bool LightSlave::getStatus() {
    getData();
    return state_packet.data.light.target_state;
}

int LightSlave::getId() { return id; }

void LightSlave::setData(void* data) {
    uint8_t* value = (uint8_t*)data;

    char command[256] = {0};
    snprintf(command, sizeof(command) - 1, "/usr/sbin/i2cset -y 1 0x%02x 0x%02x i", id, *value);

    popen(command, "r");
}

void LightSlave::start(int i2c_fd) { fd = i2c_fd; }

void LightSlave::stop() { fd = -1; }
