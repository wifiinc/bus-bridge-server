#include "RGBSlave.h"

RGBSlave::RGBSlave(uint8_t id, uint8_t i2c_address) : id(id), i2c_address(i2c_address) {}

void* RGBSlave::getData() {
    uint8_t r, g, b;

    r = wiringPiI2CRead(fd);
    g = wiringPiI2CRead(fd);
    b = wiringPiI2CRead(fd);

    color_state.R = r;
    color_state.G = g;
    color_state.B = b;

    return;
}

bool RGBSlave::getStatus() {
    
    getData();
    if (color_state.R == 0 && color_state.G == 0 && color_state.B == 0) {
        return false;
    } else {
        return true;
    }

}

int RGBSlave::getId() { return id; }

void RGBSlave::setData(void* data) {
    RGBData* rgb_data = (RGBData*)data;
    uint8_t r = rgb_data->R;
    uint8_t g = rgb_data->G;
    uint8_t b = rgb_data->B;

    wiringPiI2CWrite(fd, r);
    wiringPiI2CWrite(fd, g);
    wiringPiI2CWrite(fd, b);
}

void RGBSlave::start(int i2c_fd) { fd = i2c_fd; }

void RGBSlave::stop() { fd = -1; }
