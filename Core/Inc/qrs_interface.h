#ifndef QRS_INTERFACE_H
#define QRS_INTERFACE_H

static int test_flag = 0;

int qrs_detection_task_get_test_flag();
void qrs_detection_task_set_test_flag();
void qrs_detection_task_drop_test_flag();

int qrs_get_local_buffer_ready_flag();

void qrs_add_new_sample(int32_t new_sample);
void qrs_add_new_isoline(int32_t isoline_value);
void qrs_add_order_number(uint32_t received_ecg_samples_counter);
int qrs_get_new_sample_flag();
void qrs_set_new_sample_flag(int flag);

int get_new_rr_interval_flag();
void set_new_rr_interval_flag(int flag);
uint32_t qrs_get_new_rr_interval();

void qrs_action();

#endif // QRS_INTERFACE_H
