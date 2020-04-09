#include "power_button_obj.h"
#include "power_button_interface.h"
#include "timer_250hz_interface.h"

void power_button_action()
{
	if(button_tick_start_marker > 0)  // uzhe videli, chto knopka nazhata
	{
		if((power_button_GPIO_Port->IDR & power_button_Pin) != (uint32_t)GPIO_PIN_RESET) // knopka nazhata
		{
			if(timer_250hz_get_tick() > POWER_OFF_INTERVAL) // nazhata bolshe 2 sekund
			{
				// dva raza migaem krasnym-zelenym
				HAL_GPIO_WritePin(GPIOC, blue_led_Pin, GPIO_PIN_SET);
				for(int i=0; i<2; i++)
				{
					HAL_GPIO_WritePin(GPIOC, green_led_Pin, GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOC, red_led_Pin, GPIO_PIN_SET);
					for(volatile long i=0; i<1500000; i++);
					HAL_GPIO_WritePin(GPIOC, green_led_Pin, GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOC, red_led_Pin, GPIO_PIN_RESET);
					for(volatile long i=0; i<1500000; i++);
				}

				HAL_GPIO_WritePin(GPIOC, red_led_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOC, green_led_Pin, GPIO_PIN_SET);

				HAL_GPIO_WritePin(power_on_GPIO_Port, power_on_Pin, GPIO_PIN_RESET); // power off

				while(1);

			}
			else // nazhata menshe 2 sekund
			{
				// turn blue led on
				HAL_GPIO_WritePin(GPIOC, blue_led_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOC, red_led_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOC, green_led_Pin, GPIO_PIN_SET);
			}
		}

	}
	else  // esche ne videli, chto knopka nazhata
	{
		if((power_button_GPIO_Port->IDR & power_button_Pin) != (uint32_t)GPIO_PIN_RESET) // knopka nazhata
		{
			// power button is pressed
			button_tick_start_marker = timer_250hz_get_tick();
			// turn blue led on
			HAL_GPIO_WritePin(GPIOC, blue_led_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, red_led_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOC, green_led_Pin, GPIO_PIN_SET);
		}
	}
}


