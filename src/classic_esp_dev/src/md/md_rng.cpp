#include "md_rng.h"

#ifndef DR_REG_RNG_BASE
#define DR_REG_RNG_BASE  0X3FF75144
#endif

/**
 * @brief H/W乱数生成器から乱数を取得
 * 
 * @return uint32_t 
 */
uint32_t md_rng_get(void)
{
    // 2us待ち後にRNGのレジスタ読み出し
    delayMicroseconds(2);

    return (uint32_t)READ_PERI_REG(DR_REG_RNG_BASE);
}