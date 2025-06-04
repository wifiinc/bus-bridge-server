#pragma once

#include <wiringPi.h>
#include <wiringPiI2C.h>

class BaseSlave {
   public:
    virtual ~BaseSlave() = default;
    virtual void* getData() = 0;
    virtual bool getStatus() = 0;
    virtual int getId() = 0;
    virtual void setData(void* data) = 0;
    virtual void start(int i2c_fd) = 0;
    virtual void stop() = 0;
};