#pragma once

class BaseSlave {
public:
    virtual ~BaseSlave() = default;
    virtual void* getData() = 0;
    virtual void* getStatus() = 0;
    virtual int getId() = 0;
    virtual void setData(void* data) = 0;
    virtual void start() = 0;
    virtual void stop() = 0;
};