#include "timer_250hz_obj.h"
#include "timer_250hz_interface.h"

#include "ad7792_interface.h"

#include "tim.h"
#include "usart.h"

#include "ecg_ring_buffer_interface.h"
#include "isoline_interface.h"
#include "heart_rate_interface.h"

static char message[128];

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
		timer_250hz_tick++;

		//uint32_t sample = 0;
		uint32_t sample = ad7792_read_data();
		ecg_ring_buffer_push(sample);
		isoline_add_new_sample(sample);

		/*
		sprintf(message, "%uI%u\r\n", (unsigned int)sample, (unsigned int)sample);

		int i;
		for(i=0; i<strlen(message); i++)
		{
			// wait for TXE
			while((huart1.Instance->SR & UART_FLAG_TXE) != UART_FLAG_TXE);
			// now TX register is empty, we can transmit
			huart1.Instance->DR = (uint16_t)message[i];
		}
		//*/

		if(timer_250hz_counter >= 500)
		{
			timer_250hz_counter = 0;
			HAL_GPIO_TogglePin(GPIOC, green_led_Pin);

			sprintf(message, "c%dp%03dm%dv%03db%03di%08ldG\r\n", 1, get_current_heartrate(), 5, 83, 171, (long int)1003007);
			HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen(message), 500);  //send escape sequence if connection is active

		}
	}
}

void timer_250hz_start()
{
	__HAL_TIM_ENABLE_IT(&htim2, TIM_IT_UPDATE);
	__HAL_TIM_ENABLE(&htim2);
}

uint32_t timer_250hz_get_tick()
{
	return timer_250hz_tick;
}
