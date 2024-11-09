#ifndef _APP_OTA_H_
#define _APP_OTA_H_

#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <Update.h>

#include "../app_main.h"

#define __WEBSERVER_PORT__  80
#define __OTA_DEBUG__        0x01

void APP_OTA_Init(void);
void APP_OTA_Req_Catch(void);
#endif
