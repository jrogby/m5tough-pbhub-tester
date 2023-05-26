#pragma once

/*
    Note 1:
        The default range of the ADC input voltage of the built-in MCU is 0-5V,
        and the corresponding ADC resolution is 10bit (1024),
        so when using an analog signal input with an input range less than 5V,
        it will not reach the maximum The value is 1024.
    Note 2:
        Not all Units with a black interface (PortB) support expansion through PbHUB.
        PbHUB can only be applied to basic single-bus communication,
        through the I2C protocol (built-in MEGA328) to achieve basic digital read and write,
        analog Read and write.
        But for units such as Weight (built-in HX711) that not only need to read anglog,
        but also depend on the timing of the Unit, PbHUB cannot be expanded.
*/
#include <Wire.h>

#define PBHUB_IIC_ADDR 0x61
#define PBHUB_PORT0_ADDR 0x40
#define PBHUB_PORT1_ADDR 0x50
#define PBHUB_PORT2_ADDR 0x60
#define PBHUB_PORT3_ADDR 0x70
#define PBHUB_PORT4_ADDR 0x80
#define PBHUB_PORT5_ADDR 0xA0

#define PBHUB_PORT_TYPE_A 0 // PortA, I2C
#define PBHUB_PORT_TYPE_B 1 // PortB, GPIO

class PbHub
{
  public:
    enum class Channels {CH0, CH1, CH2, CH3, CH4, CH5};
    static const uint8_t MAX_CHANNELS = 6;
    static const uint8_t I2C_ADDR = 0x61;
    static const uint8_t ANALOG_READ_DATA_LEN = 2;

    PbHub();
    void begin();

    uint8_t a_digital(uint8_t portAddr);
    uint16_t b_analog(uint8_t portAddr);
    uint8_t b_digital(uint8_t portAddr);

    PbHub(uint8_t inputPin);
    uint16_t analogRead(Channels ch);

  private:
    static const uint8_t HUB_ADDRS[MAX_CHANNELS];
};
