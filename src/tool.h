// #pragma once
// #include <Arduino.h>
// #include "M5StickCPlus2.h"
// #include <M5GFX.h>
// #include <lgfx/v1/panel/Panel_ST7789.hpp>
// #include "Button.h"

// #include <WiFi.h>
// #include <HTTPClient.h>

// #include <esp_wifi.h>

// #include "arduinoFFT.h"

#pragma once
#include <Arduino.h>
#include "M5StickCPlus2.h"
#include <M5GFX.h>
#include <lgfx/v1/panel/Panel_ST7789.hpp>
#include "Button.h"
#include <Wire.h>

#include <BLE2902.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <WiFi.h>
#include <HTTPClient.h>

#include <esp_wifi.h>

#include "arduinoFFT.h"

#define tft M5.Lcd

#define MAX_VOLTAGE 4300.0;

extern const unsigned char ImageData[768];
extern const unsigned char icon_wifi[4608];

void tool_setup();
void tool_loop();

void wifi_test();
