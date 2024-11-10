#include "tool.h"

namespace TOOL
{
    void TEST::hardware_init()
    {
        /* Hold pwr pin */
        gpio_reset_pin((gpio_num_t)POWER_HOLD_PIN);
        pinMode(POWER_HOLD_PIN, OUTPUT);
        digitalWrite(POWER_HOLD_PIN, HIGH);
        Wire1.begin(I2C_SDA_PIN, I2C_SCL_PIN);
    }

  void TOOL::setup() {
      hardware_init();
      key_init();
      lcd_init();
  }

  void TOOL::loop() {
      wifi_test();

      display->setFont(&fonts::Font0);
      display->setTextSize(1);
      displayUpdate();
  }
}