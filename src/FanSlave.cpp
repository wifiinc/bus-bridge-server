#include "FanSlave.h"
#include <stdio.h>

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

//    char command[128] = { 0 };
//    snprintf(command, sizeof(command) - 1, "i2cset -y 1 0x%02X 0x%02X", id, current_speed);
//    printf("%s\n", command);
//    popen(command, "r");
    wiringPiI2CWrite(fd, current_speed);
}

void FanSlave::start(int i2c_fd) { fd = i2c_fd; }

void FanSlave::stop() { fd = -1; }
