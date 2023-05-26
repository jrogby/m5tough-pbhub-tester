#include "PbHub.h"

const uint8_t PbHub::HUB_ADDRS[] = {0x40, 0x50, 0x60, 0x70, 0x80, 0xA0};

PbHub::PbHub() {}

void PbHub::begin()
{
    Wire.begin();
}

uint16_t PbHub::b_analog(uint8_t reg)
{
    Wire.beginTransmission(PBHUB_IIC_ADDR);
    Wire.write(reg | 0x06);
    Wire.endTransmission();

    uint8_t RegValue_L = 0, RegValue_H = 0;

    Wire.requestFrom(PBHUB_IIC_ADDR, 2);
    while (Wire.available())
    {
        RegValue_L = Wire.read();
        RegValue_H = Wire.read();
    }

    return (RegValue_H << 8) | RegValue_L;
}

uint8_t PbHub::a_digital(uint8_t reg)
{
    Wire.beginTransmission(PBHUB_IIC_ADDR);
    Wire.write(reg | 0x04);
    Wire.endTransmission();

    uint8_t RegValue = 0;

    Wire.requestFrom(PBHUB_IIC_ADDR, 1);
    while (Wire.available())
    {
        RegValue = Wire.read();
    }
    return RegValue;
}

uint8_t PbHub::b_digital(uint8_t reg)
{
    Wire.beginTransmission(PBHUB_IIC_ADDR);
    Wire.write(reg | 0x05);
    Wire.endTransmission();

    uint8_t RegValue = 0;

    Wire.requestFrom(PBHUB_IIC_ADDR, 1);
    while (Wire.available())
    {
        RegValue = Wire.read();
    }
    return RegValue;
}


uint16_t PbHub::analogRead(Channels ch) {
    uint8_t low = 0;
    uint8_t high = 0;

    Wire.beginTransmission(I2C_ADDR);
    Wire.write(HUB_ADDRS[static_cast<size_t>(ch)] | 0x06);
    Wire.endTransmission();

    Wire.requestFrom(I2C_ADDR, ANALOG_READ_DATA_LEN);
    while (Wire.available()) {
        low = Wire.read();
        high = Wire.read();
    }
    return (high << 8) | low;
}