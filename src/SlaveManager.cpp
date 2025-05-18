#include "SlaveManager.h"

#include <cstdint>
#include <stdexcept>

#include "CO2Slave.h"
#include "DoorSlave.h"
#include "RGBSlave.h"
#include "packets.h"

SlaveManager::SlaveManager() {}

void SlaveManager::initialize() {
    /*
     * WiringPI setup here;
     */

    /* if (setup_failed) {
     *  throw std::runtime_error("I2C setup failed")
     * };
     */

    throw std::runtime_error("SlaveManager::initialize() not implemented yet");
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
        // case /* door */:
        //     newSlave = new DoorSlave(id, i2c_address);
        //     break;
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
