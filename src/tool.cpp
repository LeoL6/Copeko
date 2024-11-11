#include "tool.h"

void tool_setup() {
    auto cfg = M5.config();
    StickCP2.begin(cfg);
    tft.setRotation(1);
    tft.setTextColor(GREEN);
    tft.setTextDatum(middle_center);
    tft.setTextFont(&fonts::Orbitron_Light_24);
    tft.setTextSize(0.6);
}

void tool_loop() {
    wifi_test();
    // delay(10);
    // displayUpdate();
    StickCP2.update();
}
