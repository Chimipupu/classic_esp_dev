#include "../wifi/app_ota.h"
#include "../wifi/app_wifi.h"
#include "../ble/app_ble.h"

const char* loginIndex =
    "<form name='loginForm'>"
        "<table width='50%' bgcolor='37C924' align='center'>"
            "<tr>"
                "<td colspan=2>"
                    "<center><font size=4><b>ESP32 OTA Update(F/W REV.0.11)</b></font></center>"
                    "<br>"
                "</td>"
                "<br>"
                "<br>"
            "</tr>"
            "<td>User:</td>"
            "<td><input type='text' size=25 name='userid'><br></td>"
            "</tr>"
            "<br>"
            "<br>"
            "<tr>"
                "<td>Password:</td>"
                "<td><input type='Password' size=25 name='pwd'><br></td>"
                "<br>"
                "<br>"
            "</tr>"
            "<tr>"
                "<td><input type='submit' onclick='check(this.form)' value='Login'></td>"
            "</tr>"
        "</table>"
    "</form>"
    "<script>"
        "function check(form)"
        "{"
        "if(form.userid.value=='admin' && form.pwd.value=='admin')"
        "{"
        "window.open('/serverIndex')"
        "}"
        "else"
        "{"
        " alert('Error Password or Username')/*displays error message*/"
        "}"
        "}"
    "</script>";

/*
 * Server Index Page
 */
const char* serverIndex = 
    "<script src='https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js'></script>"
    "<form method='POST' action='#' enctype='multipart/form-data' id='upload_form'>"
    "<div id='prga'>OTA Update (F/W = *.bin) </div>"
    "<br>"
    "<input type='file' name='update'>"
            "<input type='submit' value='OTA Update'>"
        "</form>"
    "<div id='prg'>Progress: 0%</div>"
    "<script>"
    "$('form').submit(function(e){"
    "e.preventDefault();"
    "var form = $('#upload_form')[0];"
    "var data = new FormData(form);"
    " $.ajax({"
    "url: '/update',"
    "type: 'POST',"
    "data: data,"
    "contentType: false,"
    "processData:false,"
    "xhr: function() {"
    "var xhr = new window.XMLHttpRequest();"
    "xhr.upload.addEventListener('progress', function(evt) {"
    "if (evt.lengthComputable) {"
    "var per = evt.loaded / evt.total;"
    "$('#prg').html('progress: ' + Math.round(per*100) + '%');"
    "}"
    "}, false);"
    "return xhr;"
    "},"
    "success:function(d, s) {"
    "console.log('success!')" 
    "},"
    "error: function (a, b, c) {"
    "}"
    "});"
    "});"
    "</script>";

// extern BluetoothSerial SerialBT;

const char* p_mdns_host = "esp32";
extern const char* p_ssid;
extern const char* p_password;

WebServer ota_server(80);

void APP_OTA_Init(void)
{
    DEBUG_PRINTF_RTOS("OTA Init\n");

    /*use mdns for p_mdns_host name resolution*/
    if (!MDNS.begin(p_mdns_host)) { //http://esp32.local
        DEBUG_PRINTF_RTOS("Error setting up MDNS responder!\n");
        while (1) {
            delay(1000);
        }
    }

    DEBUG_PRINTF_RTOS("mDNS responder started\n");
    /*return index page which is stored in serverIndex */
    ota_server.on("/", HTTP_GET, []() {
        ota_server.sendHeader("Connection", "close");
        ota_server.send(200, "text/html", loginIndex);
    });
    ota_server.on("/serverIndex", HTTP_GET, []() {
        ota_server.sendHeader("Connection", "close");
        ota_server.send(200, "text/html", serverIndex);
    });
    /*handling uploading firmware file */
    ota_server.on("/update", HTTP_POST, []() {
        ota_server.sendHeader("Connection", "close");
        ota_server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
        ESP.restart();
    }, []() {
        HTTPUpload& upload = ota_server.upload();
        if (upload.status == UPLOAD_FILE_START) {
            // SerialBT.printf("OTA Update F/W: %s\n", upload.filename.c_str());s
            DEBUG_PRINTF_RTOS("OTA Update F/W: %s\n", upload.filename.c_str());
            if (!Update.begin(UPDATE_SIZE_UNKNOWN)) { //start with max available size
                Update.printError(Serial);
            }
        } else if (upload.status == UPLOAD_FILE_WRITE) {
            /* flashing firmware to ESP*/
            if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
                Update.printError(Serial);
            }
        } else if (upload.status == UPLOAD_FILE_END) {
            if (Update.end(true)) { //true to set the size to the current progress
                // SerialBT.printf("OTA Update : Success (TotalSize = %uByte)\nRebooting...\n", upload.totalSize);
                DEBUG_PRINTF_RTOS("OTA Update : Success (TotalSize = %uByte)\nRebooting...\n", upload.totalSize);
            } else {
                Update.printError(Serial);
            }
        }
    });

    DEBUG_PRINTF_RTOS("OTA server on : http://%s.local or http://%s\n", p_mdns_host, WiFi.localIP().toString().c_str());
    ota_server.begin();
}

void APP_OTA_Req_Catch(void)
{
    ota_server.handleClient();
}
