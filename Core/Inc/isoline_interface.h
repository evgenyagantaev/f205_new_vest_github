#ifndef ISOLINE_INTERFACE_H
#define ISOLINE_INTERFACE_H

void isoline_add_new_sample(uint32_t new_sample);
void calculate_isoline_value();
uint32_t get_isoline_value();
uint32_t get_last_sample();
int get_new_sample_flag();
void set_new_sample_flag(int flag);
void isoline_action();

// sluzhebnye funkcii
void shift_array(uint32_t *array, int LENGTH);
void copy_array(uint32_t *array_from, uint32_t *array_to, int LENGTH);
void sort(uint32_t *array, int LENGTH);

#endif // ISOLINE_INTERFACE_H
