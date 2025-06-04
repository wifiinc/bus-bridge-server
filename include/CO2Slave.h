#pragma once
#include <cstdint>

#include "BaseSlave.h"

struct CO2Data {
    uint16_t value;
}__attribute__((packed));

class CO2Slave : public BaseSlave {
   public:
    CO2Slave(uint8_t id, uint8_t i2c_address);

    void* getData();
    bool getStatus();
    int getId();
    void setData(void* data);
    void start(int i2c_fd);
    void stop();

   private:
    int id;
    int fd;
    uint8_t i2c_address;

    CO2Data co2data;
};
