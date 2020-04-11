#include "qrs_obj.h"
#include "qrs_interface.h"
#include "heart_rate_interface.h"

#include "gpio.h"
#include "usart.h"

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

/*
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
*/

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

//***********************************************
#define DEBUG_MARKERS
//***********************************************


//#include "ecg_ring_buffer_interface.h"
//#include "heart_rate_obj.h"
//#include "rr_window_obj.h"

//debug
//#include "usart.h"
//extern UART_HandleTypeDef huart1;




void qrs_shift_array(int32_t *array, int LENGTH)
{
	int i;
	for(i=0; i<(LENGTH-1); i++)
		array[i] = array[i+1];
}



//---------------------------------------------------------------------------
// Method detects presence of r-pick in the local qrs-window
void qrsDetect(void)
{
	if(qrs_suspend_flag) // procedure of qrs detection is suspended (just have found
	// a new r-pick)
	{
		if((order_numbers[0] - qrs_suspend_marker) > QRSSUSPENDPERIOD)
		{
			//suspend period gone yet; so we reset the suspend flag
			qrs_suspend_flag = 0;
			//GPIOB->BSRRH=GPIO_Pin_9;  //pb9 low
		}
	}
	else // qrs detection is not suspended
	{
		// first: we detect if there is an excess of threshold level in the window
		int excess = 0;
		int i = 0;
		while(!excess && (i<(QRSWINDOWLENGTH-RIGHT_WINDOW_MARGIN))) // otstupili na 7 semplov ot pravogo kraya chtoby "vlez" ves QRS-kompleks
		{
			if((qrs_window[i] - isoline_window[i]) > AMPLITUDELEASTTHRESHOLD)
			{
				excess = 1;
				base_isoline = isoline_window[i];
				r_start = i;
			}
			else
				i++;
		}

		// if no excess of threshold level in the local window, we have to drop
		// buffer and collect it again
		if(!excess)
		{
			local_buffer_ready_flag = 0;
			qrs_buffer_counter = 0;
			samples_to_drop_in_window = SAMPLES_TO_DROP_DEFAULT;

			// if no qrs more than 4 seconds, then we detect asistoly
			//*
			if(asystolyShiftCounter >= 1000)
			{
			   if(get_current_heartrate() != 444) // there was real pulse yet
				   heart_rate_set_asystoly();
			}
			//*/
		}

		// second: we detect if there is a drop under isoline level
		int drop = 0;
		if(excess)
		{
			while(!drop && (i<QRSWINDOWLENGTH))
			{
				if(qrs_window[i] < base_isoline)
				{
					drop = 1;
					r_finish = i;
				}
				else
				   i++;
			}
		}// end if(excess)

		// third: we detect if the r-pick length is ok
		int lengthOk = 0;
		if(drop)
		{
			int length = r_finish - r_start;
			if((length <= RMOSTLENGTH) && (length >= RLEASTLENGTH))
			   lengthOk = 1;
		}

		// fourth: we check amplitude
		int amplitudeOk = 0;
		if(lengthOk)
		{
			int amplitude = qrs_window[r_start];
			r_max_index = r_start;
			for(int i=(r_start+1); i<r_finish; i++)
			{
			   if(qrs_window[i] > amplitude)
			   {
				  amplitude = qrs_window[i];
				  r_max_index = i;
			   }
			}
			amplitude = amplitude - base_isoline;
			if(amplitude <= AMPLITUDEMOSTTHRESHOLD)
			   amplitudeOk = 1;
		}// end if(lengthOk)

		// now if amplitude OK, so we probably detected good r-pick
		if(amplitudeOk)
		{
			#ifdef DEBUG_MARKERS
			// set markers in array of markers
			markers[r_start] = WHITEMARKER;
			markers[r_finish] = BLUEMARKER;
			markers[r_max_index] = REDMARKER;
			#endif

			// set marker of freshly detected r-pick
			old_rmarker = r_marker;
			r_marker = order_numbers[r_max_index];

			new_rr_interval = (r_marker - old_rmarker)*4;
			new_rr_interval_calculated_flag = 1;

			// give new rr-interval to Baevsky calculation procedure
			//rr_window_set_new_rr_ready_flag(1);
			//rr_window_set_new_rr_interval(new_rr_interval);


			// reset of asystoly counter
			asystolyShiftCounter = 0;

			// drop buffer
			local_buffer_ready_flag = 0;
			qrs_buffer_counter = 0;
			samples_to_drop_in_window = r_finish;

			// now suspend a qrs detection procedure for a while
			qrs_suspend_marker = order_numbers[r_max_index];
			qrs_suspend_flag = 1;
			//GPIOB->BSRRL=GPIO_Pin_9;  //pb9 high

		}//end if(amplitudeOk)

	}//end if(qrsSuspend)

}//end qrsDetect
//--------------------------end----------------------------------------------
