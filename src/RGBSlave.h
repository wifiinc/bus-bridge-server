#pragma once
#include "BaseSlave.h"

class RGBSlave {
public:
    RGBSlave(int id);
    void* getData();
    void* getStatus();
    int getId();
    void setData(void* data);
    void start();
    void stop();
private:
    int id;
    int fd;
};