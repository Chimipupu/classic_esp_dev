/**
 * @file （ファイル名） : lib_mcu.h
 * @brief （概要） : MCUライブラリ
 * @author （作成者） : ちみ/Chimi（https://github.com/Chimipupu）
 * @date （作成日） : 2021/01/14
 * @details （詳細な説明） : 
*/

#ifndef __LIB_MCU__H__
#define __LIB_MCU__H__

#include "./common.h"
#include <esp_system.h>

#define SoC_NAME  "ESP32"
#define ESP32_PSRAM_HEAP_MAX    4194252

typedef enum _e_core_type
{
    ARM_CORTEX_M,
    ARM_CORTEX_A,
    TENSILICA,
    CORE_8BIT,
    CORE_16BIT,
    CORE_32IT,
    CORE_64BIT,
    NONE = 0xFF
} e_core_type;

typedef struct _lib_mcu_t
{
    uint8_t float_size;
    uint8_t double_size;
    uint8_t long_double_size;
    uint8_t core_type_flg;
} lib_mcu_t;

void lib_esp32_info( void );
void lib_type_size( void );
void lib_env_info( void );
void lib_MCU_Reset( void );
void lib_hw_info(void);

#define SYS_RESET   lib_MCU_Reset

#endif /* __LIB_MCU__H__ */

