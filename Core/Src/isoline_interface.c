#include "isoline_obj.h"
#include "isoline_interface.h"
#include "ecg_ring_buffer_interface.h"
#include "qrs_obj.h"



void isoline_action()
{
	//debug
	char message[64];  // remove when not debugging

	if(get_new_sample_flag())  // new sample added, and isoline is not recalculated yet
	{
		calculate_isoline_value();
		set_new_sample_flag(0); // drop flag
		int32_t last_sample = get_last_sample();
		int32_t isoline_value = get_isoline_value();
		//int32_t ecg = last_sample - isoline_value;
		int32_t ecg = isoline_value;
		qrs_add_new_sample(last_sample);
		qrs_add_new_isoline(isoline_value);
		qrs_add_order_number(get_received_ecg_samples_counter());

	}
}

void isoline_add_new_sample(uint32_t new_sample)
{
	shift_array(isoline_buffer, ISOLINE_BUFFER_LENGTH);
	isoline_buffer[ISOLINE_BUFFER_LENGTH-1] = new_sample;
	copy_array(isoline_buffer, isoline_buffer_sorted, ISOLINE_BUFFER_LENGTH);
	sort(isoline_buffer_sorted, ISOLINE_BUFFER_LENGTH);

	new_sample_added_flag = 1;
}


void calculate_isoline_value()
{
	int i;
	current_isoline = 0;
	for(i=CUT_EDGES; i<(ISOLINE_BUFFER_LENGTH-CUT_EDGES); i++)
	{
		current_isoline += isoline_buffer_sorted[i];
	}
	current_isoline /= (ISOLINE_BUFFER_LENGTH-2*CUT_EDGES);
}

uint32_t get_isoline_value()
{
	return current_isoline;
}
uint32_t get_last_sample()
{
	return isoline_buffer[ISOLINE_BUFFER_LENGTH-1];
}
//****************************************************************

int get_new_sample_flag()
{
	return new_sample_added_flag;
}
void set_new_sample_flag(int flag)
{
	new_sample_added_flag = flag;
}










