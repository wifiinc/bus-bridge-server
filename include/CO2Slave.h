#pragma once
#include <cstdint>

#include "BaseSlave.h"
#include "packets.h"

class CO2Slave : public BaseSlave {
   public:
    CO2Slave(uint8_t id, uint8_t i2c_address);

    const void* getData() override;
    bool getStatus() override;
    int getId() override;
    void setData(void* data) override;
    void start(int i2c_fd) override;
    void stop() override;

   private:
    int id;
    int fd;
    uint8_t i2c_address;
    uint16_t command;

    bool power_state = true;
    struct sensor_packet state_packet;
};
