#pragma once
#include <cstdint>

#include "BaseSlave.h"

class DoorSlave : public BaseSlave {
   public:
    DoorSlave(uint8_t id, int i2c_address);

    void* getData() override;
    void* getStatus() override;
    int getId() override;
    void setData(void* data) override;
    void start() override;
    void stop() override;

   private:
    int id;
    int fd;
};
