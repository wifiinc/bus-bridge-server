#include "BaseSlave.h"
#include <iostream>

BaseSlave::~BaseSlave() {}
void* BaseSlave::getData(){return nullptr;}
void* BaseSlave::getStatus(){return nullptr;}
void* BaseSlave::getId(){return nullptr;}
void BaseSlave::setData(void* data) {}
void BaseSlave::start() {}
void BaseSlave::stop() {}