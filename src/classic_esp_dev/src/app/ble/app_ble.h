#ifndef _APP_BLE_H_
#define _APP_BLE_H_

#include "../app_main.h"
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

/**********************************************************************************/
/* イベント */
/**********************************************************************************/
/* BLEタスク */
#define EVENT_BLE_0_INIT  (1 << 0)   /*  */
#define EVENT_BLE_1  (1 << 1)   /*  */
#define EVENT_BLE_2  (1 << 2)   /*  */
#define EVENT_BLE_3  (1 << 3)   /*  */
#define EVENT_BLE_4  (1 << 4)   /*  */
#define EVENT_BLE_5  (1 << 5)   /*  */
#define EVENT_BLE_6  (1 << 6)   /*  */
#define EVENT_BLE_7_BLE_UART  (1 << 7)   /*  */

#define EVENT_BLE_8   (1 << 8)    /*  */
#define EVENT_BLE_9   (1 << 9)    /*  */
#define EVENT_BLE_10  (1 << 10)   /*  */
#define EVENT_BLE_11  (1 << 11)   /*  */
#define EVENT_BLE_12  (1 << 12)   /*  */
#define EVENT_BLE_13  (1 << 13)   /*  */
#define EVENT_BLE_14  (1 << 14)   /*  */
#define EVENT_BLE_15  (1 << 15)   /*  */
/**********************************************************************************/
// 取得待ちイベント
#define BLE_TASK_EVENT_WAIT  \
        (EVENT_BLE_0_INIT | EVENT_BLE_7_BLE_UART)

void App_BLE_Main_Task(void *pvParameters);

#endif /* _APP_BLE_H_ */