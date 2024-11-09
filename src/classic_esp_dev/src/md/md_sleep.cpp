#include "md_sleep.h"

ESP_RTC_SLOW_MEM int g_bootCount = 0;

/**
 * @brief スリープ起床要因設定
 * 
 * @param set_wakekind スリープ起床要因(esp_sleep_wakeup_cause_t)
 */
void md_sleep_wakeup_set(uint8_t set_wakekind)
{
    switch (set_wakekind)
    {
        //********** LightSleep **********
        // UARTからの要求で起床
        case ESP_SLEEP_WAKEUP_GPIO :
            break;

        // UARTからの要求で起床
        case ESP_SLEEP_WAKEUP_UART :
            break;

#if 0
        // WiFiからの要求で起床
        case ESP_SLEEP_WAKEUP_WIFI :
            break;

        // BTからの要求で起床
        case ESP_SLEEP_WAKEUP_BT :
            break;
#endif
        //********** DeepSleep **********
        // GPIO外部割込み(EXT0)での起床
        case ESP_SLEEP_WAKEUP_EXT0 :
            // GPIO37がLOWになったら起動
            pinMode(GPIO_NUM_37, INPUT_PULLUP);
            esp_sleep_enable_ext0_wakeup(GPIO_NUM_37, LOW);
            break;

        // GPIO外部割込み(EXT1)での起床
        case ESP_SLEEP_WAKEUP_EXT1 :
            // GPIO0がLOWになったら起動
            pinMode(GPIO_NUM_0, INPUT_PULLUP);
            esp_sleep_enable_ext1_wakeup(BIT64(GPIO_NUM_0), ESP_EXT1_WAKEUP_ALL_LOW);
            break;

        // タイマ割込みでの起床
        case ESP_SLEEP_WAKEUP_TIMER :
            // 5秒ごとに起床
            esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
            DEBUG_PRINTF_RTOS("[MD DEBUG MSG] : Sleep WakeUp from Timer %d Sec\n", TIME_TO_SLEEP);
            break;

        // 静電タッチでの起床
        case ESP_SLEEP_WAKEUP_TOUCHPAD :
            break;

        // ULPからの要求で起床
        case ESP_SLEEP_WAKEUP_ULP :
            break;

        default:
            break;
    }
}

/**
 * @brief スリープ起床要因取得
 * 
 * @return uint8_t スリープ起床要因(esp_sleep_wakeup_cause_t)
 */
uint8_t md_sleep_wakeup_reson_get(void)
{
    esp_sleep_wakeup_cause_t wakeup_reason;

    wakeup_reason = esp_sleep_get_wakeup_cause();

    return ((uint8_t)wakeup_reason);
}

/**
 * @brief スリープ起床要因確認
 * 
 */
void md_sleep_wakeup_reson_check(uint8_t wakeup_reason)
{
    switch(wakeup_reason)
    {
        //********** LightSleep **********
        // UARTからの要求で起床
        case ESP_SLEEP_WAKEUP_GPIO :
            break;

        // UARTからの要求で起床
        case ESP_SLEEP_WAKEUP_UART :
            break;

#if 0
        // WiFiからの要求で起床
        case ESP_SLEEP_WAKEUP_WIFI :
            break;

        // BTからの要求で起床
        case ESP_SLEEP_WAKEUP_BT :
            break;
#endif

        //********** DeepSleep **********
        // GPIO外部割込み(EXT0)での起床
        case ESP_SLEEP_WAKEUP_EXT0 :
            DEBUG_PRINTF_RTOS("[MD DEBUG MSG] : Wakeup From EXT0\n");
            break;

        // GPIO外部割込み(EXT1)での起床
        case ESP_SLEEP_WAKEUP_EXT1 :
            DEBUG_PRINTF_RTOS("[MD DEBUG MSG] : Wakeup From EXT1\n");
            break;

        // タイマ割込みでの起床
        case ESP_SLEEP_WAKEUP_TIMER :
            DEBUG_PRINTF_RTOS("[MD DEBUG MSG] : Wakeup From Timer\n");
            break;

        // 静電タッチでの起床
        case ESP_SLEEP_WAKEUP_TOUCHPAD :
            DEBUG_PRINTF_RTOS("[MD DEBUG MSG] : Wakeup From TouchPad\n");
            break;

        // ULPから要求で起床
        case ESP_SLEEP_WAKEUP_ULP :
            DEBUG_PRINTF_RTOS("[MD DEBUG MSG] : Wakeup From ULP\n");
            break;

        //********** その他 **********
        // 通常リセット（スリープでのリセットではない）
        case ESP_SLEEP_WAKEUP_UNDEFINED :
            DEBUG_PRINTF_RTOS("[MD DEBUG MSG] : POR(Power ON Reset)\n");
            break;

        default :
            // DEBUG_PRINTF_RTOS("Wakeup was not caused by deep sleep: %d\n",wakeup_reason);
            break;
    }
}

/**
 * @brief スリープ開始
 * 
 * @param sleep_kind 
 */
void md_sleep_start(uint8_t sleep_kind)
{
    switch (sleep_kind)
    {
        // LightSleep
        case SLEEP_ESP_LIGHT :
            DEBUG_PRINTF_RTOS("[MD DEBUG MSG] : LightSleep Start\n");
            // esp_light_sleep_start();
            break;

        // DeepSleep
        case SLEEP_ESP_DEEP :
            DEBUG_PRINTF_RTOS("[MD DEBUG MSG] : DeepSleep Start\n");
            // esp_deep_sleep_start();
            break;

        default:
            break;
    }
}