#ifndef ECG_RING_BUFFER_INTERFACE_H
#define ECG_RING_BUFFER_INTERFACE_H

int ecg_ring_buffer_object_init(void);
int ecg_ring_buffer_push(uint32_t sample);
int ecg_ring_buffer_pop(uint32_t *sample);
uint32_t get_received_ecg_samples_counter();

void ecg_ring_buffer_task();

#endif // ECG_RING_BUFFER_INTERFACE_H
