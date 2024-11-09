#ifndef _COMMON_H_
#define _COMMON_H_

// C STD
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// Arduino STD
#include <Arduino.h>
#include <Wire.h>       // I2C

// ESP32
#include "sdkconfig.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "esp_task_wdt.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"
// #include <hwcrypto/aes.h>

// FreeRTOS
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/event_groups.h"
#include "freertos/semphr.h"
#include "freertos/timers.h"

extern portMUX_TYPE g_mux;
extern SemaphoreHandle_t xSerialMutex;

#define DEBUG_PRITNF    Serial.printf
// #define REG_BASE_ADDR           0xE0000000
// #define REG                     (*(volatile struct st_io *) (REG_BASE_ADDR + 0xED00))

// 割込みマスク・許可
#define __DI            portENTER_CRITICAL
#define __EI            portEXIT_CRITICAL
#define __DI_ISR        portENTER_CRITICAL_ISR
#define __EI_ISR        portEXIT_CRITICAL_ISR

#define TRUE    0x01
#define FALSE   0x00

struct st_io {                          /* struct IO    */
    union {                             /*              */
        uint8_t BYTE;                   /*  Byte Access */
        uint16_t HWORD;                 /*  2Byte Access */
        uint32_t WORD;                  /*  4Byte Access */

        struct {                        /*  Bit  Access */
                uint8_t bit_31:1;          /*    Bit 32     */
                uint8_t bit_30:1;          /*    Bit 31     */
                uint8_t bit_29:1;          /*    Bit 30     */
                uint8_t bit_28:1;          /*    Bit 29     */
                uint8_t bit_27:1;          /*    Bit 28     */
                uint8_t bit_26:1;          /*    Bit 27     */
                uint8_t bit_25:1;          /*    Bit 26     */
                uint8_t bit_24:1;          /*    Bit 25     */
                uint8_t bit_23:1;          /*    Bit 24     */
                uint8_t bit_22:1;          /*    Bit 23     */
                uint8_t bit_21:1;          /*    Bit 22     */
                uint8_t bit_20:1;          /*    Bit 21     */
                uint8_t bit_19:1;          /*    Bit 20     */
                uint8_t bit_18:1;          /*    Bit 19     */
                uint8_t bit_17:1;          /*    Bit 18     */
                uint8_t bit_16:1;          /*    Bit 17     */
                uint8_t bit_15:1;          /*    Bit 16     */
                uint8_t bit_14:1;          /*    Bit 15     */
                uint8_t bit_13:1;          /*    Bit 14     */
                uint8_t bit_12:1;          /*    Bit 13     */
                uint8_t bit_11:1;          /*    Bit 12     */
                uint8_t bit_10:1;          /*    Bit 11     */
                uint8_t bit_9:1;           /*    Bit 10     */
                uint8_t bit_8:1;           /*    Bit 9     */
                uint8_t bit_7:1;           /*    Bit 8     */
                uint8_t bit_6:1;           /*    Bit 7     */
                uint8_t bit_5:1;           /*    Bit 6     */
                uint8_t bit_4:1;           /*    Bit 5     */
                uint8_t bit_3:1;           /*    Bit 4     */
                uint8_t bit_2:1;           /*    Bit 3     */
                uint8_t bit_1:1;           /*    Bit 2     */
                uint8_t bit_0:1;           /*    Bit 1     */
        } BIT;
    } REG;
};


struct st_io_8bit {                     /* struct IO    */
    union {                             /*              */
        uint8_t BYTE;                   /*  Byte Access */

        struct {                        /*  Bit  Access */
                uint8_t bit_7:1;           /*    Bit 8     */
                uint8_t bit_6:1;           /*    Bit 7     */
                uint8_t bit_5:1;           /*    Bit 6     */
                uint8_t bit_4:1;           /*    Bit 5     */
                uint8_t bit_3:1;           /*    Bit 4     */
                uint8_t bit_2:1;           /*    Bit 3     */
                uint8_t bit_1:1;           /*    Bit 2     */
                uint8_t bit_0:1;           /*    Bit 1     */
        } BIT;
    } REG;
};

#ifdef CONFIG_IDF_TARGET_ESP32
#define CHIP_NAME "ESP32"
#endif

#ifdef CONFIG_IDF_TARGET_ESP32S2BETA
#define CHIP_NAME "ESP32-S2 Beta"
#endif

#define __WDT_ENABLE__  0x01
#define ___DEBUG___     0x01

#ifdef  WDT_ENABLE
#define WDT_TGL_FUNC    esp_task_wdt_reset()
#else
#define WDT_TGL_FUNC    __asm__ __volatile__ ("nop")
#endif

#define WDT_TGL         WDT_TGL_FUNC

// 真偽
#define TRUE            0x01
#define FALSE           0x00

// CPU種別
#define __PRO_CPU__     0x00    /* 下位層CPU (CPU#0) */
#define __APP_CPU__     0x01    /* 上位層CPU (CPU#1) */

// スリープ種別
#define SLEEP_ESP_LIGHT     0x00
#define SLEEP_ESP_DEEP      0x01

// RTC低速メモリ(2KB SRAM)
// ★DeepSleepからのリセットでも消えない)
#define ESP_RTC_SLOW_MEM    RTC_DATA_ATTR

// RTOS優先度（0～25）
#define RTOS_PRIORITY_DEAD          0   /* 最低（使わない） */
#define RTOS_PRIORITY_MINIMUM       1   /* 最低(実質) */
#define RTOS_PRIORITY_LOW           4   /* 下 */
#define RTOS_PRIORITY_MIDDLE_LOW    8   /* 中の下 */
#define RTOS_PRIORITY_MIDDLE        12  /* 中 */
#define RTOS_PRIORITY_MIDDLE_HIGH   16  /* 中の上 */
#define RTOS_PRIORITY_HIGH          20  /* 上 */
#define RTOS_PRIORITY_MAXIMUM       24  /* 最高優先度 */

// タスクリスト関数（vTaskList(char *)）に渡すバッファサイズ
// ※PSRAMからヒープで確保する
#define TASK_LIST_HEAP_SIZE 4096
// タスクリスト関数（vTaskList(char *)）を使うためのマクロ
#ifndef configUSE_TRACE_FACILITY
// #undef configUSE_TRACE_FACILITY
#define configUSE_TRACE_FACILITY		        1
#endif

#ifndef configUSE_STATS_FORMATTING_FUNCTIONS
// #undef configUSE_STATS_FORMATTING_FUNCTIONS
#define configUSE_STATS_FORMATTING_FUNCTIONS    1
#endif

#define DEBUG_PRINTF_RTOS   safeSerialPrintf
#ifdef DEBUG_PRINTF_RTOS
extern "C"
{
    static inline void safeSerialPrintf(const char *format, ...)
    {
        if (xSemaphoreTake(xSerialMutex, portMAX_DELAY) == pdTRUE) {
            // __DI(&g_mux);
            va_list args;
            va_start(args, format);

            for (const char *p = format; *p != '\0'; p++) {
                if (*p == '%') {
                    p++;  // '%'の次の文字を見る
                    int width = 0;
                    int precision = -1;

                    // 幅の取得
                    while (*p >= '0' && *p <= '9') {
                        width = width * 10 + (*p - '0');
                        p++;
                    }

                    // 精度の取得
                    if (*p == '.') {
                        p++;
                        precision = 0;
                        while (*p >= '0' && *p <= '9') {
                            precision = precision * 10 + (*p - '0');
                            p++;
                        }
                    }

                    // フォーマット指定子に基づいて処理
                    switch (*p) {
                        case 'd':  // 整数
                            Serial.print(va_arg(args, int));
                            break;
                        case 'f':  // 浮動小数点数（float）
                        case 'l':  // 'l' は無視
                        case 'F':  // 浮動小数点数（float、大文字）
                            Serial.print(va_arg(args, double), (precision >= 0) ? precision : 2);
                            break;
                        case 's':  // 文字列
                            Serial.print(va_arg(args, char*));
                            break;
                        case 'c':  // 文字
                            Serial.print((char)va_arg(args, int));
                            break;
                        case 'x':  // 16進数（小文字）
                        case 'X':  // 16進数（大文字）
                            Serial.print(va_arg(args, int), HEX);
                            break;
                        default:  // 他のフォーマット指定子はそのまま表示
                            Serial.print(*p);
                            break;
                    }
                } else if (*p == '\r' || *p == '\n') {
                    // 改行シーケンスの処理
                    Serial.println(); // 改行
                } else {
                    // '%'でない文字はそのまま表示
                    Serial.print(*p);
                }
            }
            va_end(args);
            // __EI(&g_mux);
            xSemaphoreGive(xSerialMutex);
        } else {
            Serial.println("Failed to acquire mutex!");
        }
    }
}
#endif /* DEBUG_PRINTF_RTOS */

#endif /* _COMMON_H_ */