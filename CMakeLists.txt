cmake_minimum_required(VERSION 3.10)
project(Server)

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_EXE_LINKER_FLAGS "-static")
set(CMAKE_EXE_LINKER_FLAGS "")
include_directories(include)
include_directories(ext_include)

add_library(bus_server src/BusServer.cpp)
add_library(slave_manager src/SlaveManager.cpp src/BaseSlave.cpp src/CO2Slave.cpp src/RGBSlave.cpp src/LightSlave.cpp)

find_library(wiringPi_LIB NAMES wiringPi)

add_executable(server src/main.cpp)
target_link_libraries(server bus_server slave_manager ${wiringPi_LIB})

if(NOT CMAKE_CROSSCOMPILING)
  enable_testing()
  add_subdirectory(tests)
endif()
