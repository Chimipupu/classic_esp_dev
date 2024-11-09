/**
 * @file （ファイル名） : lib_mcu.h
 * @brief （概要） : MCUライブラリ
 * @author （作成者） : ちみ/Chimi（https://github.com/Chimipupu）
 * @date （作成日） : 2021/01/14
 * @details （詳細な説明） : 
*/
#include "lib_math.h"
#include "lib_mcu.h"
#include "esp_chip_info.h"
#include <esp_system.h>
#include "esp_mac.h"

lib_mcu_t type_size;

#define ESP_FLASH_SIZE      4
// #define ESP_FLASH_SIZE      8
// #define ESP_FLASH_SIZE      16

void lib_esp32_info( void )
{
    // uint32_t tmp;
    // uint8_t *p_psram_heap;
    esp_chip_info_t chip_info;

    /* Print chip information */
    esp_chip_info(&chip_info);
    DEBUG_PRINTF_RTOS("%s(WiFi%s%s Soc)\n",
        SoC_NAME,
        (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
        (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");

    DEBUG_PRINTF_RTOS("CPU Core %d, Chip Rev.%d\n",
            chip_info.cores, chip_info.revision);

    DEBUG_PRINTF_RTOS("Flash : %dMB\n", ESP_FLASH_SIZE);

#ifdef PSRAM_ENABLE
    //  PSPRAM全ての容量を確保
    p_psram_heap = (uint8_t*) calloc( ESP32_PSRAM_HEAP_MAX , sizeof(uint8_t) );

    if(p_psram_heap != NULL)
    {
        DEBUG_PRINTF_RTOS("PSRAM Heap Get OK\r\n");
    }else{
        DEBUG_PRINTF_RTOS("ERR:PSRAM Heap Get Error\r\n");
    }

    //1バイト毎に値が書き込めるかチェック
    tmp = 0;
    while ( tmp < ESP32_PSRAM_HEAP_MAX )
    {
        p_psram_heap[tmp] = (uint8_t)tmp; //値を書き込む

        if ( p_psram_heap[tmp] != (uint8_t)tmp )  //値が合っているかチェック
        {
            // DEBUG_PRINTF_RTOS("ERR:PSRAM Heap Verify Error at %d\n", tmp);
            tmp--;
            break;
        }else{
            tmp++;
        }
    }

    // DEBUG_PRINTF_RTOS("PSRAM Heap %d Bytes Verify OK\n", tmp);
    free(p_psram_heap); //メモリの解放

    DEBUG_PRINTF_RTOS("PSRAM Heap %d Bytes\n", tmp);
#endif
}

void lib_type_size( void )
{
    type_size.float_size        = sizeof(float);
    type_size.double_size       = sizeof(double);
    type_size.long_double_size  = sizeof(long double);

    // double 型判定
    if(type_size.float_size == type_size.double_size)
    {
        type_size.core_type_flg = CORE_8BIT;
    }

    // 倍精度判定
    if(type_size.double_size != type_size.long_double_size)
    {
        type_size.core_type_flg = ARM_CORTEX_M;
    }else{
        type_size.core_type_flg = ARM_CORTEX_A;
    }
}

void lib_env_info( void )
{
    uint8_t tmp;

    lib_type_size();
    lib_esp32_info();

    DEBUG_PRINTF_RTOS("Pi = %.10f \n",math_pi());

    tmp = type_size.float_size;
    DEBUG_PRINTF_RTOS("float size(Byte) = %d \n",tmp);

    tmp = type_size.double_size;
    DEBUG_PRINTF_RTOS("double size(Byte) = %d \n",tmp);

    // double 型判定
    if(type_size.core_type_flg == CORE_8BIT)
    {
        DEBUG_PRINTF_RTOS("※8bit CPU(AVR or PIC)\r\n");
    }

    tmp = type_size.long_double_size;
    DEBUG_PRINTF_RTOS("long double size(Byte) = %d \n",tmp);

    // 倍精度判定
    if(type_size.core_type_flg != ARM_CORTEX_A)
    {
        DEBUG_PRINTF_RTOS("※倍精度\r\n");
    }else{
        DEBUG_PRINTF_RTOS("※単精度\r\n");
    }
}

void lib_MCU_Reset( void )
{
    fflush(stdout);
    esp_restart();
}

void lib_hw_info(void)
{
    uint64_t chipid;
    esp_chip_info_t chip_info;
    uint8_t tmp_mac[6];

#ifdef PSRAM_ENABLE
    DEBUG_PRINTF_RTOS("Total Heap %dByte, Free Heap %dByte",
                    ESP.getHeapSize(), ESP.getFreeHeap());
    DEBUG_PRINTF_RTOS("\n");

    DEBUG_PRINTF_RTOS("PSRAM Total Heap %dByte, PSRAM Free Heap %dByte",
                    ESP.getPsramSize(), ESP.getFreePsram());
    DEBUG_PRINTF_RTOS("\n");
#endif
    DEBUG_PRINTF_RTOS("Flash Size %dByte, Flash Speed %dMHz",
                    ESP.getFlashChipSize(), (ESP.getFlashChipSpeed() / 1000000));
    DEBUG_PRINTF_RTOS("\n");

    DEBUG_PRINTF_RTOS("ChipRev.%d, Freq %dMHz, SDK Ver.%s",
                    ESP.getChipRevision(), ESP.getCpuFreqMHz(), ESP.getSdkVersion());
    DEBUG_PRINTF_RTOS("\n");

    chipid=ESP.getEfuseMac();//The chip ID is essentially its MAC address(length: 6 bytes).
    DEBUG_PRINTF_RTOS("ESP32 Chip ID = %04X\r\n",(uint16_t)(chipid>>32));//print High 2 bytes

    DEBUG_PRINTF_RTOS("Chip Revision %d\r\n", ESP.getChipRevision());
    esp_chip_info(&chip_info);

    DEBUG_PRINTF_RTOS("Number of Core: %d\r\n", chip_info.cores);

    DEBUG_PRINTF_RTOS("CPU Frequency: %d MHz\r\n", ESP.getCpuFreqMHz());

    DEBUG_PRINTF_RTOS("Flash Chip Size = %d byte\r\n", ESP.getFlashChipSize());

    DEBUG_PRINTF_RTOS("Flash Frequency = %d Hz\r\n", ESP.getFlashChipSpeed());

    DEBUG_PRINTF_RTOS("ESP-IDF version = %s\r\n", esp_get_idf_version());

    DEBUG_PRINTF_RTOS("Free Heap Size = %d\r\n", esp_get_free_heap_size());

    // DEBUG_PRINTF_RTOS("System Free Heap Size = %d\r\n", system_get_free_heap_size());

    DEBUG_PRINTF_RTOS("Minimum Free Heap Size = %d\r\n", esp_get_minimum_free_heap_size());

    memset(tmp_mac, 0x00, sizeof(tmp_mac));
    esp_read_mac(tmp_mac, ESP_MAC_WIFI_STA);
    DEBUG_PRINTF_RTOS("[Wi-Fi Station] Mac Address = %02X:%02X:%02X:%02X:%02X:%02X\r\n", tmp_mac[0], tmp_mac[1], tmp_mac[2], tmp_mac[3], tmp_mac[4], tmp_mac[5]);

    memset(tmp_mac, 0x00, sizeof(tmp_mac));
    esp_read_mac(tmp_mac, ESP_MAC_WIFI_SOFTAP);
    DEBUG_PRINTF_RTOS("[Wi-Fi SoftAP] Mac Address = %02X:%02X:%02X:%02X:%02X:%02X\r\n", tmp_mac[0], tmp_mac[1], tmp_mac[2], tmp_mac[3], tmp_mac[4], tmp_mac[5]);

    memset(tmp_mac, 0x00, sizeof(tmp_mac));
    esp_read_mac(tmp_mac, ESP_MAC_BT);
    DEBUG_PRINTF_RTOS("[Bluetooth] Mac Address = %02X:%02X:%02X:%02X:%02X:%02X\r\n", tmp_mac[0], tmp_mac[1], tmp_mac[2], tmp_mac[3], tmp_mac[4], tmp_mac[5]);

    memset(tmp_mac, 0x00, sizeof(tmp_mac));
    esp_read_mac(tmp_mac, ESP_MAC_ETH);
    DEBUG_PRINTF_RTOS("[Ethernet] Mac Address = %02X:%02X:%02X:%02X:%02X:%02X\r\n", tmp_mac[0], tmp_mac[1], tmp_mac[2], tmp_mac[3], tmp_mac[4], tmp_mac[5]);

    // lib_env_info();
    // lib_math_accuracy();
}