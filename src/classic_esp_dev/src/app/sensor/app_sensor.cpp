#include "../sensor/app_sensor.h"
#include "../app_main.h"

// イベントハンドル
extern EventGroupHandle_t Sensor_Event_Handler;    /* Sensor */
// メッセージキューハンドル
extern QueueHandle_t  QueueHandle;

void App_Sensor_Main_Task(void *pvParameters)
{
    uint8_t ret;
    EventBits_t  evt_bit;
    msgque_t msg_q;
    msgque_data_t q_data;

    DEBUG_PRINTF_RTOS("[Task Start] : APP Sensor Task (Run Core%d)\n",xPortGetCoreID());

    for(;;)
    {
        // イベント待ち
        evt_bit = xEventGroupWaitBits( Sensor_Event_Handler, // イベントグループハンドラ
                                        SENSOR_TASK_EVENT_WAIT,  // 待ちイベント
                                        pdTRUE,
                                        pdFALSE,
                                        portMAX_DELAY );

        // Initイベント
        if((evt_bit & EVENT_SENSOR_0_INIT) != 0)
        {
            // (DEBUG)
            DEBUG_PRINTF_RTOS("[Task Msg@APP Sensor] : Init Event\n");

            // メッセージ作成
            q_data.QDataKind = Q_DATA_KIND_INIT;

            // (DEBUG)
            q_data.p_QData = NULL;

            msg_q.TaskID = APP_SENSOR_MAIN_TASK;
            msg_q.p_MsgData = &q_data;

            // キューにメッセージ送信
            ret = xQueueSend( QueueHandle, &msg_q, 0 );
        }

        // 湿温度・気圧センサイベント
        if((evt_bit & EVENT_SENSOR_2_TEMP) != 0)
        {
            // (DEBUG)
            DEBUG_PRINTF_RTOS("[Task Msg@APP Sensor] : Temp Sensor Event\n");

            // メッセージ作成
            q_data.QDataKind = Q_DATA_KIND_TEMP;
            q_data.p_QData = NULL;
            msg_q.TaskID = APP_SENSOR_MAIN_TASK;
            msg_q.p_MsgData = &q_data;

            // キューにメッセージ送信
            ret = xQueueSend( QueueHandle, &msg_q, 0 );
        }

        // IMUイベント
        if((evt_bit & EVENT_SENSOR_3_IMU) != 0)
        {
            // (DEBUG)
            DEBUG_PRINTF_RTOS("[Task Msg@APP Sensor] : IMU Sensor Event\n");

            // メッセージ作成
            q_data.QDataKind = Q_DATA_KIND_IMU;

            // (DEBUG)
            q_data.p_QData = "[IMU ACC] : X = 0, Y = 0, Z = 0\n[IMU GYRO] : X = 0, Y = 0, Z = 0";

            msg_q.TaskID = APP_SENSOR_MAIN_TASK;
            msg_q.p_MsgData = &q_data;

            // キューにメッセージ送信
            ret = xQueueSend( QueueHandle, &msg_q, 0 );
        }

        // 外付けRTCイベント
        if((evt_bit & EVENT_SENSOR_6_EXT_RTC_GET) != 0)
        {
            // (DEBUG)
            DEBUG_PRINTF_RTOS("[Task Msg@APP Sensor] : Ext RTC Event\n");

            // メッセージ作成
            q_data.QDataKind = Q_DATA_KIND_EXT_RTC;

            // (DEBUG)
            q_data.p_QData = "[NTP]:1970/1/1 00:00:00";

            msg_q.TaskID = APP_SENSOR_MAIN_TASK;
            msg_q.p_MsgData = &q_data;

            // キューにメッセージ送信
            ret = xQueueSend( QueueHandle, &msg_q, 0 );
        }

        // 超音波センサ取得イベント
        if((evt_bit & EVENT_SENSOR_9_ULRS) != 0)
        {
            // (DEBUG)
            DEBUG_PRINTF_RTOS("[Task Msg@APP Sensor] : Ultrasonic Sensor Event\n");

            // メッセージ作成
            q_data.QDataKind = Q_DATA_KIND_ULRS;

            // (DEBUG)
            q_data.p_QData = "[Ultrasonic] : 255";

            msg_q.TaskID = APP_SENSOR_MAIN_TASK;
            msg_q.p_MsgData = &q_data;

            // キューにメッセージ送信
            ret = xQueueSend( QueueHandle, &msg_q, 0 );
        }
    }
}