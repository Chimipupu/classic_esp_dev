#ifndef _APP_PWM_H_
#define _APP_PWM_H_

#include "../app_main.h"

/**********************************************************************************/
/* イベント */
/**********************************************************************************/
/* PWMタスク */
#define EVENT_PWM_0_INIT  (1 << 0)   /*  */
#define EVENT_PWM_1  (1 << 1)   /*  */
#define EVENT_PWM_2  (1 << 2)   /*  */
#define EVENT_PWM_3  (1 << 3)   /*  */
#define EVENT_PWM_4  (1 << 4)   /*  */
#define EVENT_PWM_5  (1 << 5)   /*  */
#define EVENT_PWM_6  (1 << 6)   /*  */
#define EVENT_PWM_7  (1 << 7)   /*  */

#define EVENT_PWM_8   (1 << 8)    /*  */
#define EVENT_PWM_9   (1 << 9)    /*  */
#define EVENT_PWM_10  (1 << 10)   /*  */
#define EVENT_PWM_11  (1 << 11)   /*  */
#define EVENT_PWM_12  (1 << 12)   /*  */
#define EVENT_PWM_13  (1 << 13)   /*  */
#define EVENT_PWM_14  (1 << 14)   /*  */
#define EVENT_PWM_15_MORTOR_TEST  (1 << 15)   /*  */

// 取得待ちイベント
#define PWM_TASK_EVENT_WAIT  \
        (EVENT_PWM_0_INIT | EVENT_PWM_15_MORTOR_TEST)
/**********************************************************************************/
/* ピンアサイン */
/**********************************************************************************/
#define ENA_PORT    GPIO_25     /* L298N ENA(PWM) */
// #define ENA_PORT    GPIO_32     /* L298N ENA(PWM) */
#define IN1_PORT    GPIO_4      /* L298N IN1      */
#define IN2_PORT    GPIO_27     /* L298N IN2      */

#define ENB_PORT    GPIO_26     /* L298N ENB(PWM) */
// #define ENB_PORT    GPIO_32     /* L298N ENB(PWM) */
#define IN3_PORT    GPIO_16     /* L298N IN3      */
#define IN4_PORT    GPIO_17     /* L298N IN4      */
/**********************************************************************************/

// PWMチャンネル(MAX 15CH)
#define PWM_CH_0          0x00
#define PWM_CH_1          0x01
#define PWM_CH_2          0x02
#define PWM_CH_3          0x03
#define PWM_CH_4          0x04
#define PWM_CH_5          0x05
#define PWM_CH_6          0x06
#define PWM_CH_7          0x07
#define PWM_CH_8          0x08
#define PWM_CH_9          0x09
#define PWM_CH_10         0x0A
#define PWM_CH_11         0x0B
#define PWM_CH_12         0x0C
#define PWM_CH_13         0x0D
#define PWM_CH_14         0x0E
#define PWM_CH_15         0x0F

// PWM分解能（MAX 16bit）
// #define PWM_8BIT        8
// #define PWM_10BIT       10
// #define PWM_12BIT       12
// #define PWM_14BIT       14
#define PWM_16BIT       16

#ifdef PWM_8BIT
#define PWM_FREQ_MAX   312500
#define PWM_VAL_MAX     256
#define PWM_FREQ        200   /* 2KHz */
#endif

#ifdef PWM_10BIT
#define PWM_FREQ_MAX    78125
#define PWM_VAL_MAX     1024
#define PWM_FREQ
#endif

#ifdef PWM_12BIT
#define PWM_FREQ_MAX    19531
#define PWM_VAL_MAX     4096
#define PWM_FREQ
#endif

#ifdef PWM_14BIT
#define PWM_FREQ_MAX    4883
#define PWM_VAL_MAX     16384
#define PWM_FREQ
#endif

#ifdef PWM_16BIT
#define PWM_FREQ_MAX    1220
#define PWM_VAL_MAX     65536
#define PWM_FREQ        400
#endif

// デュティー算出マクロ
#define PWM_DUTY(A) \
            (A / 100) * PWM_VAL_MAX

void App_PWM_Main_Task(void *pvParameters);

#endif /* _APP_PWM_H_ */