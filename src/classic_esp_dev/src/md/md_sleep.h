#ifndef __MD_SLEEP_H__
#define __MD_SLEEP_H__

#include "../common.h"

// 1sになるus
#define uS_TO_S_FACTOR      1000000ULL
// タイマースリープ起床時間（秒オーダー）
#define TIME_TO_SLEEP       60

void md_sleep_wakeup_set(uint8_t set_wakekind);
uint8_t md_sleep_wakeup_reson_get(void);
void md_sleep_wakeup_reson_check(uint8_t wakeup_reason);
void md_sleep_start(uint8_t sleep_kind);

#endif /* __MD_SLEEP_H__ */