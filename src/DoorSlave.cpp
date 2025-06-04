#include "DoorSlave.h"

DoorSlave::DoorSlave(uint8_t id, uint8_t i2c_address) : id(id) {}

void* DoorSlave::getData() { return nullptr; }

bool DoorSlave::getStatus() { return nullptr; }

int DoorSlave::getId() { return id; }

void DoorSlave::setData(void* data) {}

void DoorSlave::start(int i2c_fd) {}

void DoorSlave::stop() {}
