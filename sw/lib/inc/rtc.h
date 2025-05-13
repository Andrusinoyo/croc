#pragma once

#ifndef RTC_H
#define RTC_H

#include <time.h>
#include <stdint.h>
#include <stdbool.h>
#include "time_utils.h"
#include "config.h"

void rtc_enable(void);

void rtc_disable(void);

void rtc_reset(void);

struct tm rtc_get_time(void);

void rtc_set_time(struct tm* t);

int rtc_set_new_alarm(struct tm* alarm_time);

//void rtc_enable_interrupts(void);

#endif // RTC_H