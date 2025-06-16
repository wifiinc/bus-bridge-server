#pragma once

#include <cstdint>

#include "BaseSlave.h"
#include "packets.h"

typedef uint8_t FanData;

class FanSlave : public BaseSlave {
   public:
    FanSlave(uint8_t id, uint8_t i2c_address);
    const void* getData();
    bool getStatus();
    int getId();
    void setData(void* data);
    void start(int i2c_fd);
    void stop();

   private:
    int id;
    int fd;
    uint8_t i2c_address;

    FanData current_speed;

    struct sensor_packet state_packet;
};
