#include "SlaveManager.h"
#include "CO2Slave.h"

void SlaveManager::ledControl(uint8_t led_number, uint8_t led_state) {}
void SlaveManager::createSlave(int type, int id) {
    BaseSlave* newSlave = nullptr;
    switch (type) {
        case 1:
            newSlave = new CO2Slave(id);
            break;
        case 2:
            newSlave = new RGBSlave(id);
            break;
        case 3:
            newSlave = new DoorSlave();
            break;
        default:
            return; // Invalid type
    }
    slaves.push_back(newSlave);
}
void SlaveManager::deleteSlave(int id) {}
