#include "../wifi/app_ntp.h"

struct tm g_timeInfo;       //  時刻構造体
char g_ntp_buf[64] = {0};   //  文字格納用

/**
 * @brief APP NTP Init
 * 
 */
void APP_NTP_Init(void)
{
    // NTPの設定
    configTime(JST_TIME_ZONE, 0,
                "ntp.nict.jp",          // 『独立行政法人情報通信研究機構(NICT)』 NTPサーバ
                "jp.pool.ntp.org",      // 『NTP POOL PROJECT』 NTPサーバ
                "ntp.jst.mfeed.ad.jp"   // 『インターネットマルチフィード(MFEED)』NTPサーバ
                );
}

/**
 * @brief APP NTP Get Time
 * 
 * @return char* 現在時刻文字列(YYYY/MM/DD HH:MM:SS)
 */
char* APP_NTP_Get_Time(void)
{
    // NTP Get Time
    getLocalTime(&g_timeInfo);

    sprintf(g_ntp_buf, "[NTP]:%04d/%d/%d %d:%d:%d",
            g_timeInfo.tm_year + 1900, g_timeInfo.tm_mon + 1, g_timeInfo.tm_mday,
            g_timeInfo.tm_hour, g_timeInfo.tm_min, g_timeInfo.tm_sec);

    return g_ntp_buf;
}