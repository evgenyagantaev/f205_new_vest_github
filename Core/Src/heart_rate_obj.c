#include "heart_rate_obj.h"

uint32_t hr_calculate_average(uint32_t *array, int LENGTH)
{
	uint32_t return_value = 0;
	int i;

	for(i=0; i<LENGTH; i++)
		return_value += array[i];
	return_value /= LENGTH;

	return return_value;
}

double abs_dbl(double data)
{
	if(data < 0)
		return -data;
	else
		return data;
}








