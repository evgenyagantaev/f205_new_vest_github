#ifndef INC_HEART_RATE_CALCULATION_TASK_H_
#define INC_HEART_RATE_CALCULATION_TASK_H_

void heart_rate_action();

void heart_rate_init();

int get_current_heartrate();
void heart_rate_set_asystoly();
void hr_set_new_rr_interval(uint32_t interval);
void heart_rate_calculate(void);

#endif /* INC_HEART_RATE_CALCULATION_TASK_H_ */
