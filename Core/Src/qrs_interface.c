#include "qrs_obj.h"
#include "qrs_interface.h"

#include "gpio.h"
#include "usart.h"
//extern UART_HandleTypeDef huart1;
//extern USBD_HandleTypeDef USBD_Device;

void qrs_action()
{
	if(qrs_get_new_sample_flag())
	{
		qrs_set_new_sample_flag(0);   // drop flag
		if(qrs_get_local_buffer_ready_flag())
			qrsDetect();


		//*
		sprintf(message, "%dI%d\r\n", qrs_window[0], isoline_window[0]);
		//sprintf(message, "%dI%d\r\n", qrs_window[0] - isoline_window[0], 0);
		//sprintf(message, "%dI%d\r\n", isoline_window[0], isoline_window[0]);
		HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen(message), 500);  // for production board

		/*
		if(markers[0] == WHITEMARKER)
			HAL_UART_Transmit(&huart1, "W\r\n", 3, 500);  // for production board
		else if(markers[0] == BLUEMARKER)
			HAL_UART_Transmit(&huart1, "B\r\n", 3, 500);  // for production board
		//*/

		if(markers[0] == REDMARKER)
			HAL_UART_Transmit(&huart1, "R\r\n", 3, 500);  // for production board


		/*
		//debug
		if(qrs_detection_task_get_test_flag())
		{
			//sprintf(&message[1], "%ldI%ld\r\n", qrs_window[0], isoline_window[0]);
			//USBD_CUSTOM_HID_SendReport(&USBD_Device, (uint8_t *)message, strlen(message));


		}
		//*/




	}
}

int qrs_detection_task_get_test_flag()
{
	return test_flag;
}
void qrs_detection_task_set_test_flag()
{
	test_flag = 1;
}
void qrs_detection_task_drop_test_flag()
{
	test_flag = 0;
}

void qrs_add_new_sample(int32_t new_sample)
{
	qrs_shift_array(qrs_window, WINDOW_LENGTH);
	qrs_window[WINDOW_LENGTH-1] = new_sample;
	qrs_shift_array(markers, WINDOW_LENGTH);
	markers[WINDOW_LENGTH-1] = 0;

	qrs_new_sample_added_flag = 1;  // set new sample flag

	// check if local buffer (full) ready for analysis
	if(!local_buffer_ready_flag)
	{
	 // buffer is not ready, so we have not collected enough samples in it,
	 // so we increment samples counter
		qrs_buffer_counter++;
	 // if buffer is full, set flag of buffer readiness
	 if(qrs_buffer_counter >= samples_to_drop_in_window)
		 local_buffer_ready_flag = 1;
	}

	// inkrementiruem schetchik asistolii, kotoryi obnulyaetsya kazhdyi raz, kogda detektirovan qrs-kompleks
	asystolyShiftCounter++;
}

void qrs_add_new_isoline(int32_t isoline_value)
{
	qrs_shift_array(isoline_window, WINDOW_LENGTH);
	isoline_window[WINDOW_LENGTH-1] = isoline_value;
}

void qrs_add_order_number(uint32_t received_ecg_samples_counter)
{
	qrs_shift_array(order_numbers, WINDOW_LENGTH);
	order_numbers[WINDOW_LENGTH-1] = received_ecg_samples_counter;
}

int qrs_get_local_buffer_ready_flag()
{
	return local_buffer_ready_flag;
}

int qrs_get_new_sample_flag()
{
	return qrs_new_sample_added_flag;
}
void qrs_set_new_sample_flag(int flag)
{
	qrs_new_sample_added_flag = flag;
}

int get_new_rr_interval_flag()
{
	return new_rr_interval_calculated_flag;
}
void set_new_rr_interval_flag(int flag)
{
	new_rr_interval_calculated_flag = flag;
}
uint32_t qrs_get_new_rr_interval()
{
	return new_rr_interval;
}
