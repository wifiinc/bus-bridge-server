#include "FanSlave.h"

FanSlave::FanSlave(uint8_t id, uint8_t i2c_address) : id(id), i2c_address(i2c_address) {}

const void* FanSlave::getData() { return &current_speed; }

bool FanSlave::getStatus() {
    if (current_speed == 0) {
        return false;
    } else {
        return true;
    }
}

int FanSlave::getId() { return id; }

void FanSlave::setData(void* data) {
    current_speed = *(uint8_t*)data;

    wiringPiI2CWrite(fd, current_speed);
}

void FanSlave::start(int i2c_fd) { fd = i2c_fd; }

void FanSlave::stop() { fd = -1; }
