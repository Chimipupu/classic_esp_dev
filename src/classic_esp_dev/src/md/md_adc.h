#ifndef __MD_ADC_H__
#define __MD_ADC_H__

#include "../common.h"

void md_adc_init(esp_adc_cal_characteristics_t adc_val);
void md_adc_get(adc_channel_t adc_ch,
                esp_adc_cal_characteristics_t adc_val,
                uint32_t volt);


#endif /* __MD_ADC_H__ */