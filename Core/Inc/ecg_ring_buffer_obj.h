#ifndef ECG_RING_BUFFER_OBJ_H
#define ECG_RING_BUFFER_OBJ_H

#include "main.h"

#define ECGBUFFERLENGTH 64

// locals
static uint32_t received_ecg_samples_counter;

static uint32_t ecg_ring_buffer[ECGBUFFERLENGTH];
static uint32_t current_ecg_push_index;
static uint32_t current_ecg_pop_index;

int ecg_overflow_flag;

// ���������� 0
int ecg_ring_buffer_initialization(void);


#endif // ECG_RING_BUFFER_OBJ_H
