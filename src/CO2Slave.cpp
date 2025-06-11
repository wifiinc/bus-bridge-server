#include "CO2Slave.h"

#include "packets.h"

CO2Slave::CO2Slave(uint8_t id, uint8_t i2c_address) : id(id) {
    state_packet.header.ptype = PacketType::DATA;
    state_packet.header.length = sizeof(struct sensor_packet_co2);

    state_packet.data.rgb_light.metadata.sensor_id = id;
    state_packet.data.rgb_light.metadata.sensor_type = SensorType::CO2;
    command = 0x2003;
    uint8_t* command_ptr = (uint8_t*)&command; 

    wiringPiI2CWrite(fd, command_ptr[0]);
    wiringPiI2CWrite(fd, command_ptr[1]);
}

const void* CO2Slave::getData() {
    command = 0x2008;
    uint8_t* command_ptr = (uint8_t*)&command; 
    wiringPiI2CWrite(fd, command_ptr[0]);
    wiringPiI2CWrite(fd, command_ptr[1]);
    uint8_t* value_ptr = (uint8_t*)&state_packet.data.co2.value;

    value_ptr[1] = wiringPiI2CRead(fd);
    value_ptr[0] = wiringPiI2CRead(fd);
    uint8_t empty = wiringPiI2CRead(fd);
    return &state_packet;
}

bool CO2Slave::getStatus() {
    return power_state;
}

int CO2Slave::getId() { return id; }

void CO2Slave::setData(void* data) {
    return;
}

void CO2Slave::start(int i2c_fd) { fd = i2c_fd; }

void CO2Slave::stop() { fd = -1; }
