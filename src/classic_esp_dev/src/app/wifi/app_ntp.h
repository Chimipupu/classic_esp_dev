#ifndef __APP_NTP_H__
#define __APP_NTP_H__

#include "../wifi/app_wifi.h"

// JSTタイムゾーン
#define JST_TIME_ZONE         (3600 * 9)

void APP_NTP_Init(void);
char* APP_NTP_Get_Time(void);

#endif /* __APP_NTP_H__ */