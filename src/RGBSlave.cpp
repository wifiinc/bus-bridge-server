#include "RGBSlave.h"

RGBSlave::RGBSlave(int id): id(id){}

void* RGBSlave::getData() {return nullptr;}

void* RGBSlave::getStatus() {return nullptr;}

int RGBSlave::getId() {return id;}

void RGBSlave::setData(void* data) {}

void RGBSlave::start() {}

void RGBSlave::stop() {}
