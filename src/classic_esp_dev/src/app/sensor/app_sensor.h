#ifndef _APP_SENSOR_H_
#define _APP_SENSOR_H_

#include "../app_main.h"

/* イベント */
/**********************************************************************************/
/* センサタスク */
#define EVENT_SENSOR_0_INIT  (1 << 0)   /*  */
#define EVENT_SENSOR_1  (1 << 1)   /*  */
#define EVENT_SENSOR_2_TEMP  (1 << 2)   /*  */
#define EVENT_SENSOR_3_IMU  (1 << 3)   /*  */
#define EVENT_SENSOR_4  (1 << 4)   /*  */
#define EVENT_SENSOR_5_EXT_RTC_SET  (1 << 5)   /*  */
#define EVENT_SENSOR_6_EXT_RTC_GET  (1 << 6)   /*  */
#define EVENT_SENSOR_7  (1 << 7)   /*  */

#define EVENT_SENSOR_8   (1 << 8)    /*  */
#define EVENT_SENSOR_9_ULRS   (1 << 9)    /* 超音波センサ取得 */
#define EVENT_SENSOR_10  (1 << 10)   /*  */
#define EVENT_SENSOR_11  (1 << 11)   /*  */
#define EVENT_SENSOR_12  (1 << 12)   /*  */
#define EVENT_SENSOR_13  (1 << 13)   /*  */
#define EVENT_SENSOR_14  (1 << 14)   /*  */
#define EVENT_SENSOR_15  (1 << 15)   /*  */
/**********************************************************************************/

// 取得待ちイベント
#define SENSOR_TASK_EVENT_WAIT  \
        (EVENT_SENSOR_0_INIT | EVENT_SENSOR_2_TEMP | \
        EVENT_SENSOR_3_IMU | EVENT_SENSOR_5_EXT_RTC_SET | \
        EVENT_SENSOR_6_EXT_RTC_GET | EVENT_SENSOR_9_ULRS)


void App_Sensor_Main_Task(void *pvParameters);

#endif /* _APP_SENSOR_H_ */