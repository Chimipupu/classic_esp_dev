#include "../pwm/app_pwm.h"
#include "../app_main.h"

// PWM出力マクロ
#define PWM_Out(A,B)    ledcWrite(A,B)

// イベントハンドル
extern EventGroupHandle_t PWM_Event_Handler;       /* PWM */
// メッセージキューハンドル
extern QueueHandle_t  QueueHandle;

static void pwm_init(void);

// 正転
static void mot_forward(void);
// 逆転
static void mot_back(void);
// 停止
static void mot_stop(void);
// PWM
static void mot_pwm(uint8_t pwmval);

static void mot_check(void);
static void mot_pwm_check(void);
static void mot_test(void);

/**
 * @brief PWM Init
 * 
 */
static void pwm_init(void)
{
    // ledcSetup( PWM_CH_0, PWM_FREQ, PWM_16BIT );
    // ledcAttachPin(ENA_PORT, PWM_CH_0);
    ledcAttachChannel(ENA_PORT, PWM_FREQ, PWM_16BIT, PWM_CH_0);

    // ledcSetup( PWM_CH_1, PWM_FREQ, PWM_16BIT );
    // ledcAttachPin(ENB_PORT, PWM_CH_1);
    ledcAttachChannel(ENB_PORT, PWM_FREQ, PWM_16BIT, PWM_CH_1);

    pinMode(IN1_PORT, OUTPUT);
    pinMode(IN2_PORT, OUTPUT);
    pinMode(IN3_PORT, OUTPUT);
    pinMode(IN4_PORT, OUTPUT);
}

/**
 * @brief モータ正転
 * 
 */
static void mot_forward(void)
{
    // 左モータ
    digitalWrite(IN1_PORT, HIGH);
    digitalWrite(IN2_PORT, LOW);

    // 右モータ
    digitalWrite(IN3_PORT, HIGH);
    digitalWrite(IN4_PORT, LOW);
}

/**
 * @brief 逆転
 * 
 */
static void mot_back(void)
{
    // 左モータ
    digitalWrite(IN1_PORT, LOW);
    digitalWrite(IN2_PORT, HIGH);

    // 右モータ
    digitalWrite(IN3_PORT, LOW);
    digitalWrite(IN4_PORT, HIGH);
}

/**
 * @brief 停止
 * 
 */
static void mot_stop(void)
{
    // 左モータ
    digitalWrite(IN1_PORT, LOW);
    digitalWrite(IN2_PORT, LOW);

    // 右モータ
    digitalWrite(IN3_PORT, LOW);
    digitalWrite(IN4_PORT, LOW);
}

/**
 * @brief モータテスト（正転・逆転）
 * 
 */
static void mot_check(void)
{
    PWM_Out(PWM_CH_0, PWM_DUTY(50));
    PWM_Out(PWM_CH_1, PWM_DUTY(50));

    // 正転
    mot_forward();
    delay(2000);

    // 逆転
    mot_back();
    delay(2000);

    mot_stop();
}

/**
 * @brief モータPWMテスト（加速・減速）
 * 
 */
static void mot_pwm_check(void)
{
    uint8_t tmp;

    mot_forward();

    DEBUG_PRINTF_RTOS("PWM ... 0 -> 255\n");
    for(tmp = 0; tmp < PWM_VAL_MAX; tmp++)
    {
        PWM_Out(PWM_CH_0, tmp);
        PWM_Out(PWM_CH_1, tmp);
        // delay(20);
    }

    DEBUG_PRINTF_RTOS("PWM ... 255 -> 0\n");
    for(tmp = PWM_VAL_MAX; tmp >= 0; tmp--)
    {
        PWM_Out(PWM_CH_0, tmp);
        PWM_Out(PWM_CH_1, tmp);
        delay(100);
    }

    mot_stop();
}

/**
 * @brief モータテスト
 * 
 */
static void mot_test(void)
{
    // モータテスト（正転・逆転）
    DEBUG_PRINTF_RTOS("[Task Msg@APP PWM] : Motor Test, Forward -> Back\n");
    mot_check();
#if 1
    delay(3000);

    // モータPWMテスト（加速・減速）
    DEBUG_PRINTF_RTOS("[Task Msg@APP PWM] : Motor Test, Speed Up -> Speed Down\n");
    mot_pwm_check();
    delay(3000);
#endif
}

void App_PWM_Main_Task(void *pvParameters)
{
    uint8_t ret;
    EventBits_t  evt_bit;
    msgque_t msg_q;
    msgque_data_t q_data;

    DEBUG_PRINTF_RTOS("[Task Start] : APP PWM Task (Run Core%d)\n",xPortGetCoreID());

    for(;;)
    {
        // イベント待ち
        evt_bit = xEventGroupWaitBits( PWM_Event_Handler, // イベントグループハンドラ
                                        PWM_TASK_EVENT_WAIT,  // 待ちイベント
                                        pdTRUE,
                                        pdFALSE,
                                        portMAX_DELAY );

        // Initイベント
        if((evt_bit & EVENT_PWM_0_INIT) != 0)
        {
            // (DEBUG)
            DEBUG_PRINTF_RTOS("[Task Msg@APP PWM] : Iint Event\n");

            // PWM Init
            pwm_init();

            // メッセージ作成
            q_data.QDataKind = Q_DATA_KIND_INIT;

            // (DEBUG)
            q_data.p_QData = NULL;

            msg_q.TaskID = APP_PWM_MAIN_TASK;
            msg_q.p_MsgData = &q_data;

            // キューにメッセージ送信
            ret = xQueueSend( QueueHandle, &msg_q, 0 );
        }

        // モーターテストイベント
        if((evt_bit & EVENT_PWM_15_MORTOR_TEST) != 0)
        {
            // (DEBUG)
            DEBUG_PRINTF_RTOS("[Task Msg@APP PWM] : Mortor Test Event\n");

            // モーターテスト
            mot_test();

            // メッセージ作成
            q_data.QDataKind = Q_DATA_KIND_MOTOR_TEST;

            // (DEBUG)
            q_data.p_QData = NULL;

            msg_q.TaskID = APP_PWM_MAIN_TASK;
            msg_q.p_MsgData = &q_data;

            // キューにメッセージ送信
            ret = xQueueSend( QueueHandle, &msg_q, 0 );
        }
        else{
            // イベントなし???
        }
    }
}