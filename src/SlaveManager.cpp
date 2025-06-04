#include "SlaveManager.h"

#include <wiringPi.h>
#include <wiringPiI2C.h>

#include <cstdint>
#include <stdexcept>

#include "CO2Slave.h"
#include "TemperatureSlave.h"
#include "RGBSlave.h"
#include "packets.h"

#define MASTER_ADDRESS 0x01

SlaveManager::SlaveManager() : address(MASTER_ADDRESS) {}

void SlaveManager::initialize() {
    // maybe need setup not sure.

    i2c_fd = wiringPiI2CSetup(address);
    if (-1 == i2c_fd) {
        throw std::runtime_error("I2C setup failed");
    } else {
        printf("I2C setup succesful");
    };
}

void SlaveManager::ledControl(uint8_t led_number, uint8_t led_state) {}

void SlaveManager::createSlave(SensorType type, uint8_t id, int i2c_address) {
    BaseSlave* newSlave = nullptr;
    switch (type) {
        case SensorType::CO2:
            newSlave = new CO2Slave(id, i2c_address);
            break;
        case SensorType::RGB_LIGHT:
            newSlave = new RGBSlave(id, i2c_address);
            break;
        case SensorType::TEMPERATURE
            newSlave = new TemperatureSlave(id, i2c_address);
            break;
        default:
            return;  // Invalid type
    }
    slaves[id] = newSlave;
}
void SlaveManager::deleteSlave(uint8_t id) {
    if (nullptr != slaves[id]) {
        /*
         * Disconnect I2C device from bus
         */
        delete slaves[id];
    }
}

BaseSlave* SlaveManager::getSlave(int id) { return slaves[id]; }
