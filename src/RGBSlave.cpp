#include "RGBSlave.h"

#include "packets.h"

RGBSlave::RGBSlave(uint8_t id, uint8_t i2c_address) : id(id), i2c_address(i2c_address) {
    state_packet.header.ptype = PacketType::DATA;
    state_packet.header.length = sizeof(struct sensor_packet_rgb_light);

    state_packet.data.rgb_light.metadata.sensor_id = id;
    state_packet.data.rgb_light.metadata.sensor_type = SensorType::RGB_LIGHT;
}

const void* RGBSlave::getData() {
    uint8_t r, g, b;

    r = wiringPiI2CRead(fd);
    g = wiringPiI2CRead(fd);
    b = wiringPiI2CRead(fd);

    color_state.R = r;
    color_state.G = g;
    color_state.B = b;

    state_packet.data.rgb_light.red_state = r;
    state_packet.data.rgb_light.green_state = g;
    state_packet.data.rgb_light.blue_state = b;

    return &state_packet;
}

bool RGBSlave::getStatus() {
    getData();
    if (color_state.R == 0 && color_state.G == 0 && color_state.B == 0) {
        return false;
    } else {
        return true;
    }
}

int RGBSlave::getId() { return id; }

void RGBSlave::setData(void* data) {
    RGBData* rgb_data = (RGBData*)data;
    uint8_t r = rgb_data->R;
    uint8_t g = rgb_data->G;
    uint8_t b = rgb_data->B;

    wiringPiI2CWrite(fd, r);
    wiringPiI2CWrite(fd, g);
    wiringPiI2CWrite(fd, b);
}

void RGBSlave::start(int i2c_fd) { fd = i2c_fd; }

void RGBSlave::stop() { fd = -1; }
