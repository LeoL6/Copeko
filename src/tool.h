#pragma once
#include <Arduino.h>
#include <M5GFX.h>
#include <lgfx/v1/panel/Panel_ST7789.hpp>
#include "Button.h"

#include <WiFi.h>
#include <HTTPClient.h>

#include <esp_wifi.h>

#include "arduinoFFT.h"

#define display Disbuff
#define displayUpdate Displaybuff

#define MAX_VOLTAGE 4300.0;

class CLite_GFX : public lgfx::LGFX_Device
{
    lgfx::Panel_ST7789 _panel_instance;
    lgfx::Bus_SPI _bus_instance;
    lgfx::Light_PWM _light_instance;

public:
    CLite_GFX(void)
    {
        {
            auto cfg = _bus_instance.config();

            cfg.pin_mosi = LCD_MOSI_PIN;
            cfg.pin_miso = LCD_MISO_PIN;
            cfg.pin_sclk = LCD_SCLK_PIN;
            cfg.pin_dc = LCD_DC_PIN;
            cfg.freq_write = 40000000;

            _bus_instance.config(cfg);
            _panel_instance.setBus(&_bus_instance);
        }
        {
            auto cfg = _panel_instance.config();

            cfg.invert = true;
            cfg.pin_cs = LCD_CS_PIN;
            cfg.pin_rst = LCD_RST_PIN;
            cfg.pin_busy = LCD_BUSY_PIN;
            cfg.panel_width = 135;
            cfg.panel_height = 240;
            cfg.offset_x = 52;
            cfg.offset_y = 40;

            _panel_instance.config(cfg);
        }
        {                                        
            auto cfg = _light_instance.config(); 

            cfg.pin_bl = 27;
            cfg.invert = false;
            cfg.freq = 200;     
            cfg.pwm_channel = 7; 

            _light_instance.config(cfg);
            _panel_instance.setLight(&_light_instance);
        }

        setPanel(&_panel_instance);
    }
};

extern const unsigned char ImageData[768];
extern const unsigned char icon_wifi[4608];

namespace TEST
{

    class TEST
    {
    private:
        void hardware_init();

        inline void _tone(unsigned int frequency, unsigned long duration = 0UL) { tone(BUZZ_PIN, frequency, duration); }
        inline void _noTone() { noTone(BUZZ_PIN); }

        /* Display */
        CLite_GFX lcd;
        LGFX_Sprite *Disbuff;

        void Displaybuff();
        void ColorBar();

        void frame_test();
        void color_test();
        void lcd_init();
        void lcd_test();

        /* Keys */
        void key_init();
        void key_test();
        Button btnA = Button(37, 20);
        Button btnB = Button(39, 20);
        Button btnPWR = Button(35, 20);
        void checkReboot();
        bool checkNext();
        void waitNext();

        /* Wifi */
        void wifi_init();
        void wifi_test();
        void wifi_display_test_mode();
        void wifi_display_normal_mode();

    public:
        TEST() : is_test_mode(false) {}
        ~TEST() {}

        inline void setTestMode(bool testMode) { is_test_mode = testMode; }

        void setup();
        void loop();
    };

}