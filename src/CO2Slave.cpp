#include "CO2Slave.h"

CO2Slave::CO2Slave(uint8_t id, uint8_t i2c_address) : id(id), i2c_address(i2c_address) {}

void* CO2Slave::getData() {
    uint16_t value;

    value = wiringPiI2CRead(fd);
    
    co2data.value = value;
    
    return; 
}

bool CO2Slave::getStatus() {
    getData();
    if (co2data.value == 0){
        return false;
    } else {
        return true;
    }
}

int CO2Slave::getId() { return id; }

void CO2Slave::setData(void* data) {
    CO2Data* co2_data = (CO2Data*)data;
    uint16_t value = co2_data->value;

    wiringPiI2CWrite(fd, value);
}

void CO2Slave::start(int i2c_fd) { fd = i2c_fd; }

void CO2Slave::stop() { fd = -1; }
