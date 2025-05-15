#pragma once
#include <vector>
#include "BaseSlave.h"

class SlaveManager {
public:
    static void ledControl(uint8_t led_number, uint8_t led_state);
    void createSlave(int type, int id);
    void deleteSlave(int id);
    BaseSlave* getSlave(int id);

private:
    std::vector<BaseSlave*> slaves;
};