#ifndef _APP_MAIN_H_
#define _APP_MAIN_H_

#include "../common.h"

// drv
// #include "../drv/LSM303/drv_lsm303dlhc.h"
// #include "../drv/BME280/drv_bme280.h"

// md
#include "../md/md_sleep.h"
// #include "../md/md_crypto.h"
#include "../md/md_adc.h"

// Lib
#include "../lib_math.h"
#include "../lib_mcu.h"

// App
#include "../app/wifi/app_wifi.h"
// #include "../app/ble/app_ble.h"
#include "../app/pm/app_pm.h"
#include "../app/sensor/app_sensor.h"
#include "../app/pwm/app_pwm.h"

// #define WDT_ENABLE
// #define PSRAM_ENABLE
#define WIFI_ENABLE
// #define OTA_ENABLE
// #define BLE_ENABLE

typedef enum __GPIO_E{
    GPIO_0 = 0,
    GPIO_1,
    GPIO_2,
    GPIO_3,
    GPIO_4,
    GPIO_5,
    GPIO_6,
    GPIO_7,
    GPIO_8,
    GPIO_9,
    GPIO_10,
    GPIO_11,
    GPIO_12,
    GPIO_13,
    GPIO_14,
    GPIO_15,
    GPIO_16,
    GPIO_17,
    GPIO_18,
    GPIO_19,
    GPIO_20,
    GPIO_21,
    GPIO_22,
    GPIO_23,
    GPIO_24,
    GPIO_25,
    GPIO_26,
    GPIO_27,
    GPIO_28,
    GPIO_29,
    GPIO_30,
    GPIO_31,
    GPIO_32,
    GPIO_33,
    GPIO_34,
    GPIO_35,
    GPIO_36 = 36
} GPIO_E;

/* メッセージキュー */
/**********************************************************************************/
#define MSG_MAX     10  /* メッセージ最大数 */
#define MSG_SIZE    32  /* メッセージ最大サイズ */

// タスクID 列挙型
typedef enum __TASK_ID_E{
    APP_MAIN_TASK = 0,
    APP_WIFI_MAIN_TASK,
    APP_BLE_MAIN_TASK,
    APP_PM_MAIN_TASK,
    APP_SENSOR_MAIN_TASK,
    APP_PWM_MAIN_TASK,
#ifdef ___DEBUG___
    APP_DEBUG_TASK = 0xFF
#endif
} TASK_ID_E;

// メッセージキュー　データ種別 列挙型
typedef enum __Q_DATA_KIND_E{
    // 初期化(共通)
    Q_DATA_KIND_INIT = 0,

    // WiFi Task
    Q_DATA_KIND_OTA,
    Q_DATA_KIND_NTP,

    // BLE Task
    Q_DATA_KIND_BLE_UART,

    // PM Task
    Q_DATA_KIND_DEEPSLEEP,

    // Sensor Task
    Q_DATA_KIND_IMU,
    // Q_DATA_KIND_ADC,
    Q_DATA_KIND_ULRS,
    Q_DATA_KIND_TEMP,
    Q_DATA_KIND_EXT_RTC,

    // PWM Task
    Q_DATA_KIND_MOTOR_PWM,
    Q_DATA_KIND_MOTOR_TEST,
} Q_DATA_KIND_E;

// メッセージキューデータ構造体
typedef struct {
    Q_DATA_KIND_E QDataKind;   /*  メッセージキュー　データ種別 */
    char* p_QData;          /* メッセージデータポインタ */
} msgque_data_t;

// メッセージキュー送信データ構造体
typedef struct {
    TASK_ID_E TaskID;           /*  タスクID */
    msgque_data_t* p_MsgData;   /* メッセージデータポインタ */
} msgque_t;

/**********************************************************************************/

void App_Init(void);
void App_Main_Task(void *pvParameters);

#endif /* _APP_MAIN_H_ */