#ifndef ISOLINE_INTERFACE_H
#define ISOLINE_INTERFACE_H

void isoline_add_new_sample(uint32_t new_sample);
void calculate_isoline_value();
uint32_t get_isoline_value();
uint32_t get_last_sample();
int get_new_sample_flag();
void set_new_sample_flag(int flag);
void isoline_action();

#endif // ISOLINE_INTERFACE_H
