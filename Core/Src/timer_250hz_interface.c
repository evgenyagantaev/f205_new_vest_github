#include "timer_250hz_obj.h"
#include "timer_250hz_interface.h"

#include "tim.h"




void timer_250hz_flag_set()
{
	timer_250hz_flag = 1;
}
void timer_250hz_flag_reset()
{
	timer_250hz_flag = 0;
}
int timer_250hz_flag_get()
{
	return timer_250hz_flag;
}

void timer_250hz_object_init()
{
	timer_250hz_flag = 0;
	timer_250hz_counter = 0;
}


void timer_250hz_action()
{
	if(timer_250hz_flag)
	{
		timer_250hz_flag = 0;
		timer_250hz_counter++;

		if(timer_250hz_counter >= 250)
		{
			timer_250hz_counter = 0;
			HAL_GPIO_TogglePin(GPIOC, green_led_Pin);
		}
	}
}

void timer_250hz_start()
{
	__HAL_TIM_ENABLE_IT(&htim2, TIM_IT_UPDATE);
	__HAL_TIM_ENABLE(&htim2);
}
