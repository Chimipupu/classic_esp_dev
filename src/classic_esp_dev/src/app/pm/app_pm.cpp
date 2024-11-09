#include "../pm/app_pm.h"
#include "../app_main.h"

// イベントハンドル
extern EventGroupHandle_t PM_Event_Handler;        /* PM */
// メッセージキューハンドル
extern QueueHandle_t  QueueHandle;

void App_PM_Main_Task(void *pvParameters)
{
    uint8_t ret;
    EventBits_t  evt_bit;
    msgque_t msg_q;
    msgque_data_t q_data;

    DEBUG_PRINTF_RTOS("[Task Start] : APP PM Task (Run Core%d)\n",xPortGetCoreID());

    for(;;)
    {
        // イベント待ち
        evt_bit = xEventGroupWaitBits( PM_Event_Handler,      // イベントグループハンドラ
                                        PM_TASK_EVENT_WAIT,   // 待ちイベント
                                        pdTRUE,
                                        pdFALSE,
                                        portMAX_DELAY );

        // Initイベント
        if((evt_bit & EVENT_PM_0_INIT) != 0)
        {
            uint8_t wakeup_reason;

            // (DEBUG)
            DEBUG_PRINTF_RTOS("[Task Msg@APP PM] : Init Event\n");

            // メッセージ作成
            q_data.QDataKind = Q_DATA_KIND_INIT;
            q_data.p_QData = NULL;
            msg_q.TaskID = APP_PM_MAIN_TASK;
            msg_q.p_MsgData = &q_data;

            // キューにメッセージ送信
            ret = xQueueSend( QueueHandle, &msg_q, 0 );

            // スリープ起床要因取得
            wakeup_reason = md_sleep_wakeup_reson_get();
            // スリープ起床要因確認
            md_sleep_wakeup_reson_check(wakeup_reason);
        }

        // DeepSleepイベント
        if((evt_bit & EVENT_PM_6_DEEPSLEEP) != 0)
        {
            // (DEBUG)
            DEBUG_PRINTF_RTOS("[Task Msg@APP PM] : DeepSleep Event\n");

            // メッセージ作成
            q_data.QDataKind = Q_DATA_KIND_DEEPSLEEP;
            q_data.p_QData = NULL;
            msg_q.TaskID = APP_PM_MAIN_TASK;
            msg_q.p_MsgData = &q_data;

            // キューにメッセージ送信
            ret = xQueueSend( QueueHandle, &msg_q, 0 );

            // DeepSleep
            md_sleep_wakeup_set(ESP_SLEEP_WAKEUP_TIMER);
            md_sleep_start(SLEEP_ESP_DEEP);
        }
    }
}