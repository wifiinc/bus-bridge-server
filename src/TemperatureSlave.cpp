#include "TemperatureSlave.h"

TemperatureSlave::TemperatureSlave(uint8_t id, uint8_t i2c_address)
    : id(id), i2c_address(i2c_address) {}

void* TemperatureSlave::getData() {
    int temp = 0;
    char command[256] = {0};
    snprintf(command, sizeof(command) - 1, "/usr/sbin/i2cset -y 1 0x%02x 0x21 0x30 i",
             id);
    popen(command, "r");
    temp = wiringPiI2CRead(fd) << 8;
    temp |= wiringPiI2CRead(fd);
    return;
}

bool TemperatureSlave::getStatus() {
    getData();
    if (temperature.Temp == 0) {
        return false;
    } else {
        return true;
    }
}

int TemperatureSlave::getId() { return id; }

void TemperatureSlave::setData(void* data) {
    TemperatureData* temp_data = (TemperatureData*)data;
    int temp = temp_data->Temp;

    wiringPiI2CWrite(fd, temp);
}

void TemperatureSlave::start(int i2c_fd) { fd = i2c_fd; }

void TemperatureSlave::stop() { fd = -1; }