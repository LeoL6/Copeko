/**
 * @file battery.ino
 * @author SeanKwok (shaoxiang@m5stack.com)
 * @brief M5StickCPlus2 get battery voltage
 * @version 0.1
 * @date 2023-12-12
 *
 *
 * @Hardwares: M5StickCPlus2
 * @Platform Version: Arduino M5Stack Board Manager v2.0.9
 * @Dependent Library:
 * M5GFX: https://github.com/m5stack/M5GFX
 * M5Unified: https://github.com/m5stack/M5Unified
 * M5StickCPlus2: https://github.com/m5stack/M5StickCPlus2
 */

#include "M5StickCPlus2.h"
#include "image.h"
#include <math.h>
#include <WiFi.h>

#define MAX_VOLTAGE 4300.0;

// Replace with your WiFi credentials
const char* ssid = "Graham Clan";
const char* password = "trailers";

int oldVol = 0;

String ip = "NOT CONNECTED";

void setup() {
    Serial.begin(115200);
    // WiFi.begin(ssid, password);
    // while (WiFi.status() != WL_CONNECTED) {
    //   delay(1000);
    //   Serial.println("Connecting to WiFi...");
    // }
    
    // Serial.println("Connected to WiFi");

    auto cfg = M5.config();
    StickCP2.begin(cfg);
    StickCP2.Display.setRotation(1);
    StickCP2.Display.setTextColor(GREEN);
    StickCP2.Display.setTextDatum(middle_center);
    StickCP2.Display.setTextFont(&fonts::Orbitron_Light_24);
    StickCP2.Display.setTextSize(0.6);
}

const char* asciiArt[] = {
  " .-.-. ",
  "(     )",
  " \   / ",
  "  '-'  "
};

void loop() {
    StickCP2.update();
    StickCP2.Display.clear();

    if (StickCP2.BtnA.wasClicked()) {
      if (WiFi.status() != WL_CONNECTED) {
        WiFi.begin(ssid, password);
        StickCP2.Display.setTextSize(0.8);
        StickCP2.Display.setTextColor(GREEN);
        StickCP2.Display.setCursor(10, 50);
        StickCP2.Display.printf("Connecting to WiFi...");
        while (WiFi.status() != WL_CONNECTED) {
          delay(1000);
          Serial.println("Connecting to WiFi...");
        }
        Serial.println("Connected to WiFi");
        ip = WiFi.localIP().toString();
        StickCP2.Display.clear();
      } else {
        Serial.println("Already connected to WiFi");
      }
    }

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

    // int remainder = oldVol - vol;
    // int timeInMinutes = vol / (remainder * 60);
    // StickCP2.Display.setCursor(10, 50);
    // StickCP2.Display.printf("TIME LEFT: %imins", timeInMinutes);

    StickCP2.Display.setTextSize(0.6);
    StickCP2.Display.setTextColor(RED);
    StickCP2.Display.setCursor(10, 100);
    StickCP2.Display.printf("IP address: %s", ip);

    int startX = 120;  // Starting X position
    int startY = 10;  // Starting Y position
    int lineHeight = 20;  // Space between lines

    // Loop through each line in the ASCII art array
    for (int i = 0; i < 4; i++) {
      StickCP2.Display.setCursor(startX, startY + i * lineHeight);
      StickCP2.Display.print(asciiArt[i]);
    }

    // StickCP2.Display.pushImage(10, 10, 48, 48, slot_cherry);

    delay(1000);
    // oldVol = vol;
}
