#ifndef HEART_RATE_OBJ_H
#define HEART_RATE_OBJ_H

#include "main.h"

// heart rate buffers length
#define REGULARANDQUARANTINEBUFFERLENGTH 5
// maximum appropriate deviation of heart rate from mean value of buffer
// (percents)
static const uint16_t MAXHEARTRATEDEVIATION = 10;

static int current_heartrate;
//static int heart_rate_measurement_started = 0;
static uint32_t new_rr_interval;
static uint32_t new_heart_rate;
static uint32_t regular_average;
static uint32_t quarantine_average;

uint32_t regular_heart_rate_buffer[REGULARANDQUARANTINEBUFFERLENGTH];
uint32_t quarantine_heart_rate_buffer[REGULARANDQUARANTINEBUFFERLENGTH];
static int new_regular_heart_rate_ready_flag = 0;






#endif // HEART_RATE_OBJ_H
