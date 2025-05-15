#pragma once
#include "BaseSlave.h"

class CO2Slave : public BaseSlave {
public:
    CO2Slave(int id);
    void* getData() override;
    void* getStatus() override;
    int getId();
    void setData(void* data) override;
    void start() override;
    void stop() override;
private:
    int id;
};