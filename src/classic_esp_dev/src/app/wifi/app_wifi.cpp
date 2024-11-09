#include "../wifi/app_wifi.h"
#include "../wifi/app_ota.h"
#include "app_ntp.h"

#include "../app_main.h"

// セマフォハンドル
extern SemaphoreHandle_t RF_Semphr_Handler;
// メッセージキューハンドル
extern QueueHandle_t  QueueHandle;
// イベントハンドル
extern EventGroupHandle_t WiFi_Event_Handler;

static void wifi_init( void );

const char* p_ssid     = "B4865595449D-2G";
const char* p_password = "55351108940066";

static bool s_ota = false;

static void wifi_init( void )
{
    // Connect to WiFi network
    WiFi.begin(p_ssid, p_password);
    DEBUG_PRINTF_RTOS("\n");

    // Wait for connection
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    DEBUG_PRINTF_RTOS("\n");
    DEBUG_PRINTF_RTOS("SSID:%s\n", p_ssid);
    DEBUG_PRINTF_RTOS("IP:%s\n", WiFi.localIP().toString().c_str());
}

void App_WiFi_Main_Task(void *pvParameters)
{
    uint8_t ret;
    EventBits_t  evt_bit;
    msgque_t msg_q;
    msgque_data_t q_data;
    char* p_ntp_data;

    DEBUG_PRINTF_RTOS("[Task Start] : APP WiFi Task (Run Core%d)\n",xPortGetCoreID());

    for(;;)
    {
        // イベント待ち
        evt_bit = xEventGroupWaitBits( WiFi_Event_Handler,      // イベントグループハンドラ
                                        WIFI_TASK_EVENT_WAIT,   // 待ちイベント
                                        pdTRUE,
                                        pdFALSE,
                                        portMAX_DELAY );

        // イベントがあれば
        if(evt_bit > 0){
#ifdef BLE_ENABLE
            // RFセマフォ取得待ち（RFはBLEと排他）
            ret = xSemaphoreTake( RF_Semphr_Handler, portMAX_DELAY );

            // セマフォが取れたのでWiFi処理
            if(ret != pdFALSE)
#endif
            {
                // WiFi Initイベント
                if((evt_bit & EVENT_WIFI_0_INIT) != 0){
                    wifi_init();

                    // NTP 初期化
                    APP_NTP_Init();

                    // メッセージ作成
                    q_data.QDataKind = Q_DATA_KIND_INIT;
                    q_data.p_QData = NULL;
                    msg_q.TaskID = APP_WIFI_MAIN_TASK;
                    msg_q.p_MsgData = &q_data;

                    // キューにメッセージ送信
                    ret = xQueueSend( QueueHandle, &msg_q, 0 );

                    // (DEBUG)
                    DEBUG_PRINTF_RTOS("[Task Msg@APP WiFi] : Init Event\n");
                }

                // NTPイベント
                if((evt_bit & EVENT_WIFI_10_NTP) != 0){
                    // NTPから現在時刻取得
                    p_ntp_data = APP_NTP_Get_Time();

                    // メッセージ作成
                    q_data.QDataKind = Q_DATA_KIND_NTP;
                    q_data.p_QData = p_ntp_data;
                    msg_q.TaskID = APP_WIFI_MAIN_TASK;
                    msg_q.p_MsgData = &q_data;

                    // キューにメッセージ送信
                    ret = xQueueSend( QueueHandle, &msg_q, 0 );

                    // (DEBUG)
                    DEBUG_PRINTF_RTOS("[Task Msg@APP WiFi] : NTP Get Event\n");
                }

                // OTAイベント
                if((evt_bit & EVENT_WIFI_13_OTA) != 0){
                    DEBUG_PRINTF_RTOS("[Task Msg@APP WiFi] : OTA Proc Event\n");
                    APP_OTA_Init();
                    s_ota = true;
                    DEBUG_PRINTF_RTOS("[Task Msg@APP WiFi] : OTA Server Start\n");
                }
#ifdef BLE_ENABLE
                // RFセマフォ解放
                xSemaphoreGive( RF_Semphr_Handler );
#endif
            }
        }

        if(s_ota != false){
            APP_OTA_Req_Catch();
            vTaskDelay(1 / portTICK_PERIOD_MS);
        }
    }
}