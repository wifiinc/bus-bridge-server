#pragma once
#include <cstdint>

#include "BaseSlave.h"

struct RGBData {
    bool on;
    uint8_t R, G, B;
} __attribute__((packed));

class RGBSlave : public BaseSlave {
   public:
    RGBSlave(uint8_t id, int i2c_address);
    void* getData();
    void* getStatus();
    int getId();
    void setData(void* data);
    void start();
    void stop();

   private:
    int id;
    int fd;

    bool power_state;
    RGBData color_state;
};
