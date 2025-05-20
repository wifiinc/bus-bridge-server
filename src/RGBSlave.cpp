#include "RGBSlave.h"

RGBSlave::RGBSlave(uint8_t id, uint8_t i2c_address) : id(id), i2c_address(i2c_address) {}

void* RGBSlave::getData() { return nullptr; }

void* RGBSlave::getStatus() { return nullptr; }

int RGBSlave::getId() { return id; }

void RGBSlave::setData(void* data) {
    RGBData* rgb_data = (RGBData*)data;
    color_state = *rgb_data;

    if (rgb_data->on > 1) {
        rgb_data->on = color_state.on;
    }

    wiringPiI2CRawWrite(fd, (uint8_t*)rgb_data, sizeof(*rgb_data));
}

void RGBSlave::start(int i2c_fd) { fd = i2c_fd; }

void RGBSlave::stop() { fd = -1; }
