#ifndef _APP_WIFI_H_
#define _APP_WIFI_H_

#include "WiFi.h"
#include "../app_main.h"

#define WEB_SERVRE_PORT     80

/**********************************************************************************/
/* イベント */
/**********************************************************************************/
/* WiFiタスク */
#define EVENT_WIFI_0_INIT           (1 << 0)    /* WiFi 初期化要求イベント */
#define EVENT_WIFI_1_WIFI_CONECT    (1 << 1)    /* OTA実行要求イベント */
#define EVENT_WIFI_2_WIFI_KILL      (1 << 2)    /* NTP取得要求イベント */
#define EVENT_WIFI_3_WIFI_STA       (1 << 3)    /*  */
#define EVENT_WIFI_4_WIFI_SCAN      (1 << 4)    /*  */
#define EVENT_WIFI_5_UDP_TX         (1 << 5)    /*  */
#define EVENT_WIFI_6_UDP_RX         (1 << 6)    /*  */
#define EVENT_WIFI_7                (1 << 7)    /*  */
#define EVENT_WIFI_8                (1 << 8)    /*  */
#define EVENT_WIFI_9                (1 << 9)    /*  */
#define EVENT_WIFI_10_NTP           (1 << 10)   /*  */
#define EVENT_WIFI_11_WIFI_AP       (1 << 11)   /*  */
#define EVENT_WIFI_12_HTTPD         (1 << 12)   /*  */
#define EVENT_WIFI_13_OTA           (1 << 13)   /*  */
#define EVENT_WIFI_14               (1 << 14)   /*  */
#define EVENT_WIFI_15               (1 << 15)   /*  */
/**********************************************************************************/
// 取得待ちイベント
#define WIFI_TASK_EVENT_WAIT  \
        ( EVENT_WIFI_0_INIT | EVENT_WIFI_1_WIFI_CONECT | \
        EVENT_WIFI_2_WIFI_KILL | EVENT_WIFI_3_WIFI_STA | \
        EVENT_WIFI_4_WIFI_SCAN | EVENT_WIFI_5_UDP_TX | \
        EVENT_WIFI_6_UDP_RX | EVENT_WIFI_10_NTP | \
        EVENT_WIFI_11_WIFI_AP | EVENT_WIFI_12_HTTPD | \
        EVENT_WIFI_13_OTA )

void vTaskCore1WiFi(void *pvParameters);

#endif /* _APP_WIFI_H_ */