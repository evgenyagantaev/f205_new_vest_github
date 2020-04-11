#include "isoline_obj.h"

// PRIVATE

void shift_array(uint32_t *array, int LENGTH)
{
	int i;
	for(i=0; i<(LENGTH-1); i++)
		array[i] = array[i+1];
}
void copy_array(uint32_t *array_from, uint32_t *array_to, int LENGTH)
{
	int i;
	for(i=0; i<LENGTH; i++)
		array_to[i] = array_from[i];
}

// puzyrkovaya sortirovka
void sort(uint32_t *array, int LENGTH)
{
	int i, j;

	for(i=LENGTH; i>0; i--)
	{
		for(j=1; j<i; j++)
		{
			if(array[j]<array[j-1])	// gonim maksimalnyi vverh
			{
				uint32_t aux = array[j];
				array[j] = array[j-1];
				array[j-1] = aux;
			}
		}
	}
}
