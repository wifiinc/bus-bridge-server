#include "CO2Slave.h"

CO2Slave::CO2Slave(uint8_t id, int i2c_address) : id(id) {
    /*
     * Open I2C connection and save the FD in the 'fd' member variable
     */
}

void* CO2Slave::getData() { return nullptr; }

void* CO2Slave::getStatus() { return nullptr; }

int CO2Slave::getId() { return id; }

void CO2Slave::setData(void* data) {}

void CO2Slave::start() {}

void CO2Slave::stop() {}
