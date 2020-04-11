#ifndef HEART_RATE_OBJ_H
#define HEART_RATE_OBJ_H

#include "main.h"

#define BUFFER_LENGTH 5
// heart rate buffers length
static const uint16_t REGULARANDQUARANTINEBUFFERLENGTH = 5;
// maximum appropriate deviation of heart rate from mean value of buffer
// (percents)
static const uint16_t MAXHEARTRATEDEVIATION = 10;

static int current_heartrate;
static int heart_rate_measurement_started = 0;
static uint32_t new_rr_interval;
static uint32_t new_heart_rate;
static uint32_t regular_average;
static uint32_t quarantine_average;

uint32_t regular_heart_rate_buffer[BUFFER_LENGTH];
uint32_t quarantine_heart_rate_buffer[BUFFER_LENGTH];
static int new_regular_heart_rate_ready_flag = 0;




uint32_t hr_calculate_average(uint32_t *array, int LENGTH);

double abs_dbl(double data);


#endif // HEART_RATE_OBJ_H
