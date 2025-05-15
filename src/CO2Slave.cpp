#include "co2slave.h"

CO2Slave::CO2Slave(int id) : BaseSlave() {}
void* CO2Slave::getData() {return nullptr;}
void* CO2Slave::getStatus() {return nullptr;}
int CO2Slave::getId() {return id;}
void CO2Slave::setData(void* data) {}
void CO2Slave::start() {}
void CO2Slave::stop() {}