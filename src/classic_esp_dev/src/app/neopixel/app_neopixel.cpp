/**
 * @file app_neopixel.cpp
 * @author ちみ/Chimi（https://github.com/Chimipupu）
 * @brief NeoPixelアプリ
 * @version 0.1
 * @date 2024-10-16
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "app_neopixel.hpp"

#define MAX_BRIGHTNESS          32      // 最大輝度
#define LED_COLOR_ON_TIMER      100     // 1色の表示時間
#define RGBLED_NUM              1       // RGB LEDの数

static uint8_t s_red = 0;               // 赤
static uint8_t s_green = 0;             // 青
static uint8_t s_blue = 0;              // 緑
static uint8_t s_red_fade_val = 0;      // 赤のフェード値
static uint8_t s_gree_fade_val = 0;     // 青のフェード値
static uint8_t s_blue_fade_val = 0;     // 緑のフェード値
static uint8_t s_fade_led_no = 0;       // フェードするNeoPixelの番号
static bool s_is_fade = false;
static bool s_led_fade_amount = false;
static bool s_rgbled_fade_amount = false;
static uint8_t s_led_pwm_val = 0;

Adafruit_NeoPixel pixels(RGBLED_NUM,
                        RGBLED_PIN,
                        NEO_GRB + NEO_KHZ800);

/**
 * @brief 単色LEDのフェード
 * 
 * @param pin LEDのピン（GPIOの番号)
 */
void app_led_fade(uint8_t pin)
{
    analogWrite(pin, s_led_pwm_val);

    if (s_led_fade_amount != true) {
        s_led_pwm_val++;
        if (s_led_pwm_val == 255){
            s_led_fade_amount = !s_led_fade_amount;
        }
    } else {
        s_led_pwm_val--;
        if (s_led_pwm_val == 0){
            s_led_fade_amount = !s_led_fade_amount;
        }
    }
}

/**
 * @brief NeoPixelのフェード
 * 
 */
void app_neopixel_fade(void)
{
    if (s_is_fade != false) {
        pixels.setPixelColor(s_fade_led_no, pixels.Color(s_red_fade_val, s_gree_fade_val, s_blue_fade_val));
        pixels.show();
        if (s_rgbled_fade_amount != true) {
            if (s_red != 0) {
                s_red_fade_val++;
            }
            if (s_blue != 0){
                s_blue_fade_val++;
            }
            if (s_green != 0){
                s_gree_fade_val++;
            }
            if ((s_red_fade_val >= s_red) && (s_gree_fade_val >= s_green) && (s_blue_fade_val >= s_blue)) {
                s_red_fade_val = s_red;
                s_gree_fade_val = s_green;
                s_blue_fade_val = s_blue;
                s_rgbled_fade_amount = !s_rgbled_fade_amount;
            }
        } else {
            if (s_red != 0){
                s_red_fade_val--;
            }
            if (s_blue != 0){
                s_blue_fade_val--;
            }
            if (s_green != 0){
                s_gree_fade_val--;
            }
            if ((s_red_fade_val == 0) && (s_gree_fade_val == 0) && (s_blue_fade_val == 0)) {
                s_rgbled_fade_amount = !s_rgbled_fade_amount;
            }
        }
    } else {
        s_red_fade_val = 0;
        s_gree_fade_val = 0;
        s_blue_fade_val = 0;
        pixels.setPixelColor(s_fade_led_no, pixels.Color(s_red_fade_val, s_gree_fade_val, s_blue_fade_val));
        pixels.show();
    }
}

/**
 * @brief RGB LED 初期化
 * 
 */
void app_neopixel_init(void)
{
    pixels.begin();
    pixels.clear();
    pixels.show();
}

/**
 * @brief 指定のRGBにLEDを点灯 or 発光
 * 
 * @param red 赤
 * @param green 緑
 * @param blue 青
 * @param led_no NeoPixelの番号
 * @param is_onoff ON/OFF
 * @param is_fade フェードするか
 */
void app_neopixel_ctrl(uint8_t red,uint8_t green, uint8_t blue, uint8_t led_no, uint8_t onoff, bool is_fade)
{
    s_red = red;
    s_blue = blue;
    s_green = green;
    s_is_fade = is_fade;

    if(s_is_fade != false)
    {
        s_fade_led_no = led_no;
    }else{
        if (onoff != false) {
            pixels.setPixelColor(led_no, pixels.Color(s_red, s_green, s_blue));
            pixels.show();
        }else{
            pixels.clear();
            pixels.show();
        }
    }
}