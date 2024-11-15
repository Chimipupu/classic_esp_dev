#include "../ble/app_ble.h"
#include "../app_main.h"

// セマフォハンドル
extern SemaphoreHandle_t RF_Semphr_Handler;
// イベントハンドル
extern EventGroupHandle_t BLE_Event_Handler;       /* BLE */
// メッセージキューハンドル
extern QueueHandle_t  QueueHandle;

TaskHandle_t vTaskHandleBtSerial;

BluetoothSerial SerialBT;
// Bluetooth device name
const char* s_ble_name = "ESP32_BLE_Serial";

static void vTaskCore1BtSerial(void *p_parameter);
static void bt_serial_start(void);
static void bt_serial_main(void);

static void bt_serial_start(void)
{
    SerialBT.begin(s_ble_name);
    DEBUG_PRINTF_RTOS("BLE Serial Deveice(%s) is Running\n",s_ble_name);
}

static void bt_serial_main(void)
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

static void vTaskCore1BtSerial(void *p_parameter)
{
    DEBUG_PRINTF_RTOS("[Core1] vTaskCore1BtSerial\n");
    bt_serial_start();

    while (1)
    {
        bt_serial_main();
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

void App_BLE_Main_Task(void *pvParameters)
{
    uint8_t ret;
    EventBits_t  evt_bit;
    msgque_t msg_q;
    msgque_data_t q_data;

    DEBUG_PRINTF_RTOS("[Task Start] : APP BLE Task(Run Core%d)\n",xPortGetCoreID());

    while(1)
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
                    DEBUG_PRINTF_RTOS("[Task Msg@APP BLE] : BT Serial Task Create\n");
                    xTaskCreateUniversal(vTaskCore1BtSerial,     // タスク関数
                                        "vTaskCore1BtSerial",    // タスク名
                                        8192,                    // スタック
                                        NULL,                    // 起動パラメータ
                                        RTOS_PRIORITY_MIDDLE,    // 優先度
                                        &vTaskHandleBtSerial,    // タスクハンドラ
                                        __APP_CPU__              // 実行するコア
                                        );

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