#pragma once
#include <cstdint>

#include "BaseSlave.h"

class DoorSlave : public BaseSlave {
   public:
    DoorSlave(uint8_t id, uint8_t i2c_address);

    void* getData() override;
    bool getStatus() override;
    int getId() override;
    void setData(void* data) override;
    void start(int i2c_fd) override;
    void stop() override;

   private:
    int id;
    int fd;
};
