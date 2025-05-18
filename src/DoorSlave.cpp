#include "DoorSlave.h"

DoorSlave::DoorSlave(uint8_t id, int i2c_address) : id(id) {
    /*
     * Open I2C connection and save the FD in the 'fd' member variable
     */
}

void* DoorSlave::getData() { return nullptr; }

void* DoorSlave::getStatus() { return nullptr; }

int DoorSlave::getId() { return id; }

void DoorSlave::setData(void* data) {}

void DoorSlave::start() {}

void DoorSlave::stop() {}
