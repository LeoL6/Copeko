#include "src/tool.h"

TOOL::TOOL tool;

void setup() {
  tool.setup();

  auto cfg = M5.config();
  StickCP2.begin(cfg);
  StickCP2.Display.setRotation(1);
  StickCP2.Display.setTextColor(GREEN);
  StickCP2.Display.setTextDatum(middle_center);
  StickCP2.Display.setTextFont(&fonts::Orbitron_Light_24);
  StickCP2.Display.setTextSize(0.6);
}

void loop() {
  StickCP2.Display.clear();
  tool.loop();

  // BATTERY ICON
  int voltage = StickCP2.Power.getBatteryVoltage();

  float mult = voltage / MAX_VOLTAGE;

  // int r = round(255 * mult);
  // int g = round(255 * (1 - mult));
  // int b = 0;

  // int batteryColor = StickCP2.Display.color332(r, g, b);

  StickCP2.Display.drawRect(10, 10, 40, 20, WHITE);
  StickCP2.Display.fillRect(13, 13, 34 * mult, 15, WHITE);

  StickCP2.Display.setCursor(20, 20);
  int greyscale = 255 * (1 - mult);
  StickCP2.Display.setTextColor(StickCP2.Display.color332(greyscale, greyscale, greyscale));
  StickCP2.Display.setTextSize(0.5);
  StickCP2.Display.printf("%i", (int) round(mult * 100));

  wifi_test();

  delay(1000);
}
