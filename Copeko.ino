#include "src/tool.h"

void setup() {
  tool_setup();
}

void loop() {
  tool_loop();

  // BATTERY ICON
  int voltage = StickCP2.Power.getBatteryVoltage();

  float mult = voltage / MAX_VOLTAGE;

  // // int r = round(255 * mult);
  // // int g = round(255 * (1 - mult));
  // // int b = 0;

  // // int batteryColor = StickCP2.Display.color332(r, g, b);

  tft.drawRect(10, 2, 40, 20, WHITE);
  tft.fillRect(13, 5, 34 * mult, 15, WHITE);

  tft.setCursor(20, 12);
  int greyscale = 255 * (1 - mult);
  tft.setTextFont(&fonts::Orbitron_Light_24);
  tft.setTextColor(StickCP2.Display.color332(greyscale, greyscale, greyscale));
  tft.setTextSize(0.5);
  tft.printf("%i", (int) round(mult * 100));

  delay(100);
}
