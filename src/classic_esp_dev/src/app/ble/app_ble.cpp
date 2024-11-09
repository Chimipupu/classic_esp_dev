#include "../ble/app_ble.h"
#include "../app_main.h"

// セマフォハンドル
extern SemaphoreHandle_t RF_Semphr_Handler;
// イベントハンドル
extern EventGroupHandle_t BLE_Event_Handler;       /* BLE */
// メッセージキューハンドル
extern QueueHandle_t  QueueHandle;

BluetoothSerial SerialBT;
// Bluetooth device name
const char* s_ble_name = "ESP32_BLE_Serial";

static void App_BLE_Serial_Start(void);
static void App_BLE_Serial_Main(void);

static void App_BLE_Serial_Start(void)
{
    SerialBT.begin(s_ble_name);
    DEBUG_PRINTF_RTOS("BLE Serial Deveice(%s) is Running\n",s_ble_name);
}

static void App_BLE_Serial_Main(void)
{
    char val;

    if (Serial.available()) {
        val = Serial.read();
        Serial.write(val);
        SerialBT.write(val);
    }
    if (SerialBT.available()) {
        val = SerialBT.read();
        Serial.write(val);
        SerialBT.write(val);
    }
    delay(1);
}

void App_BLE_Main_Task(void *pvParameters)
{
    uint8_t ret;
    EventBits_t  evt_bit;
    msgque_t msg_q;
    msgque_data_t q_data;

    DEBUG_PRINTF_RTOS("[Task Start] : APP BLE Task(Run Core%d)\n",xPortGetCoreID());

    for(;;)
    {
        // イベント待ち
        evt_bit = xEventGroupWaitBits( BLE_Event_Handler,      // イベントグループハンドラ
                                        BLE_TASK_EVENT_WAIT,   // 待ちイベント
                                        pdTRUE,
                                        pdFALSE,
                                        portMAX_DELAY );

        if(evt_bit > 0)
        {
            // RFセマフォ取得待ち（RFはBLEと排他）
            ret = xSemaphoreTake( RF_Semphr_Handler,
                                portMAX_DELAY );

            // セマフォが取れたのでWiFi処理
            if(ret != pdFALSE)
            {
                // BLE Initイベント
                if((evt_bit & EVENT_BLE_0_INIT) != 0)
                {
                    // (DEBUG)
                    DEBUG_PRINTF_RTOS("[Task Msg@APP BLE] : Init Event\n");

                    // メッセージ作成
                    q_data.QDataKind = Q_DATA_KIND_INIT;
                    q_data.p_QData = NULL;
                    msg_q.TaskID = APP_BLE_MAIN_TASK;
                    msg_q.p_MsgData = &q_data;

                    // キューにメッセージ送信
                    ret = xQueueSend( QueueHandle, &msg_q, 0 );
                }

                // BLE UARTイベント
                if((evt_bit & EVENT_BLE_7_BLE_UART) != 0)
                {
                    // (DEBUG)
                    DEBUG_PRINTF_RTOS("[Task Msg@APP BLE] : BLE UART Event\n");

                    App_BLE_Serial_Start();

                    // メッセージ作成
                    q_data.QDataKind = Q_DATA_KIND_INIT;
                    q_data.p_QData = NULL;
                    msg_q.TaskID = APP_BLE_MAIN_TASK;
                    msg_q.p_MsgData = &q_data;

                    // キューにメッセージ送信
                    ret = xQueueSend( QueueHandle, &msg_q, 0 );
                }

                // RFセマフォ解放
                xSemaphoreGive( RF_Semphr_Handler );
            }
        }
    }
}