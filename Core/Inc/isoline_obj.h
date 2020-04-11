#ifndef ISOLINE_OBJ_H
#define ISOLINE_OBJ_H

#include "main.h"

#define ISOLINE_BUFFER_LENGTH 21
#define CUT_EDGES 5

static uint32_t current_isoline;

static uint32_t isoline_buffer[ISOLINE_BUFFER_LENGTH]; //
static uint32_t isoline_buffer_sorted[ISOLINE_BUFFER_LENGTH];

static int new_sample_added_flag;



// sluzhebnye funkcii
void shift_array(uint32_t *array, int LENGTH);
void copy_array(uint32_t *array_from, uint32_t *array_to, int LENGTH);
void sort(uint32_t *array, int LENGTH);

#endif // ISOLINE_OBJ_H
