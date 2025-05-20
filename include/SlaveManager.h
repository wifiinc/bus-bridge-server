#pragma once
#include <cstdint>
#include <map>
#include <vector>

#include "BaseSlave.h"
#include "packets.h"

class SlaveManager {
   public:
    SlaveManager();

    /**
     * @brief Setup the underlying I2C bus
     * @throws std__runtime_error if the I2C setup fails
     */
    void initialize();

    void ledControl(uint8_t led_number, uint8_t led_state);

    /**
     * @brief Creates a new slave device into the internal mapping
     * @details Assigns a pre-known SensorType and ID to an I2C device, and then opens the I2C
     * connection to it
     * @param type The SensorType of the sensor, as defined in packets.h
     * @param id The ID of the slave device
     * @param i2c_address The I2C address of the slave device
     */
    void createSlave(SensorType type, uint8_t id, int i2c_address);

    /**
     * @brief Unmaps the slave from the internal mapping
     * @param id The ID of the slave device to unmap
     */
    void deleteSlave(uint8_t id);

    /**
     * @brief Get a slavedevice with a given ID
     * @param id The ID of the slave device to retrieve
     */
    BaseSlave* getSlave(int id);

   private:
    bool initialized = false;

    uint8_t address = 0x01;
    int i2c_fd = -1;

    std::map<int, BaseSlave*> slaves;  // maps ID to BaseSlave ptr
};
