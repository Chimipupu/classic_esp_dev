#include "md_adc.h"

#if 0

void md_adc_init(esp_adc_cal_characteristics_t adc_val)
{
    // ADC起動
    adc_power_on();

    // ADC1_CH6 初期化
    adc_gpio_init(ADC_UNIT_1, ADC_CHANNEL_6);

    // ADC1の解像度を12bit（0~4095）に設定
    adc1_config_width(ADC_WIDTH_BIT_12);

    // ADC1の減衰を11dBに設定
    adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_DB_11);

    // 電圧値に変換パラメータを設定
    esp_adc_cal_characterize(ADC_UNIT_1,
                            ADC_ATTEN_DB_11,
                            ADC_WIDTH_BIT_12,
                            1100,
                            &adc_val);
}

/**
 * @brief 
 * 
 * @param adc_ch    ADC　CH
 * @param adc_val   ADC値
 * @param volt      ADC値の電圧変換値
 */
void md_adc_get(adc_channel_t adc_ch,
                esp_adc_cal_characteristics_t adc_val,
                uint32_t volt)
{
    esp_adc_cal_get_voltage(adc_ch, &adc_val, &volt);
}
#endif