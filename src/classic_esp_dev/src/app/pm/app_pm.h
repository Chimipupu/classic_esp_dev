#ifndef _APP_PM_H_
#define _APP_PM_H_

#include "../app_main.h"

#define TIME_MIN        60
#define TIME_HOUR       (60 * 60)
#define SLEEP_ERROR     1.006       /* Deep Sleep誤差(%) */
#define TIME_US         1000000     /* usec */

/**********************************************************************************/
/* イベント */
/**********************************************************************************/
/* PMタスク */
#define EVENT_PM_0_INIT  (1 << 0)   /*  */
#define EVENT_PM_1  (1 << 1)   /*  */
#define EVENT_PM_2  (1 << 2)   /*  */
#define EVENT_PM_3  (1 << 3)   /*  */
#define EVENT_PM_4  (1 << 4)   /*  */
#define EVENT_PM_5  (1 << 5)   /*  */
#define EVENT_PM_6_DEEPSLEEP  (1 << 6)   /*  */
#define EVENT_PM_7  (1 << 7)   /*  */

#define EVENT_PM_8   (1 << 8)    /*  */
#define EVENT_PM_9   (1 << 9)    /*  */
#define EVENT_PM_10  (1 << 10)   /*  */
#define EVENT_PM_11  (1 << 11)   /*  */
#define EVENT_PM_12  (1 << 12)   /*  */
#define EVENT_PM_13  (1 << 13)   /*  */
#define EVENT_PM_14  (1 << 14)   /*  */
#define EVENT_PM_15  (1 << 15)   /*  */
/**********************************************************************************/

// 取得待ちイベント
#define PM_TASK_EVENT_WAIT  \
        (EVENT_PM_0_INIT | EVENT_PM_6_DEEPSLEEP)

void App_PM_Main_Task(void *pvParameters);

#endif /* _APP_PM_H_ */