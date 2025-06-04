#pragma once
#include <cstdint>

#include "BaseSlave.h"
#include "packets.h"

struct RGBData {
    uint8_t R, G, B;
} __attribute__((packed));

class RGBSlave : public BaseSlave {
   public:
    RGBSlave(uint8_t id, uint8_t i2c_address);
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

    bool power_state;
    RGBData color_state;

    struct sensor_packet state_packet;
};
