#pragma once
#include <cstdint>

#include "BaseSlave.h"

struct TemperatureData {
    int Temp;
} __attribute__((packed));

class TemperatureSlave : public BaseSlave {
   public:
    TemperatureSlave(uint8_t id, uint8_t i2c_address);
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

    bool power_state;
    TemperatureData temperature;
};
