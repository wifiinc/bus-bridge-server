#include "RGBSlave.h"

RGBSlave::RGBSlave(uint8_t id, int i2c_address) : id(id) {
    /*
     * Open I2C connection and save the FD in the 'fd' member variable
     */
}

void* RGBSlave::getData() { return nullptr; }

void* RGBSlave::getStatus() { return nullptr; }

int RGBSlave::getId() { return id; }

void RGBSlave::setData(void* data) {
    RGBData* rgb_data = (RGBData*)data;

    /*
     * Tell RGB led to apply these values ^w^
     */
}

void RGBSlave::start() {}

void RGBSlave::stop() {}
