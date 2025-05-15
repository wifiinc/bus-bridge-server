#pragma once
#include "BaseSlave.h"

class DoorSlave : public BaseSlave {
public:
    void* getData() override;
    void* getStatus() override;
    void setData(void* data) override;
    void start() override;
    void stop() override;
};