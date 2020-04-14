#include "usart.h"
#include "bluetooth_obj.h"
#include "bluetooth_interface.h"




void bluetooth_obj_init()
{
	//----------------------- initialization ------------------------------------
	/*
	sprintf(message, "^#^$^%%");
	HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen(message), 500);  //send escape sequence if connection is active
	for(volatile long i=0; i<40000000; i++); //wait some time with no data to enter command mode if connection is active

	sprintf(message, "\r\n");
	HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen(message), 500);  //send escape sequence if connection is active
	for(volatile long i=0; i<40000000; i++); //wait some time with no data to enter command mode if connection is active

	sprintf(message, "AT+AB HostEvent Disable\r\n");
	HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen(message), 500); //disable notification strings, only for this session
	for(volatile long i=0; i<100000; i++);

	sprintf(message, "AT+AB Config PIN=0000\r\n");
	HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen(message), 500); //set pin
	for(volatile long i=0; i<100000; i++);

	sprintf(message, "AT+AB DefaultLocalName "DEVICENAME"\r\n");
	HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen(message), 500); //set device name***************************************************************************
	for(volatile long i=0; i<100000; i++);

	sprintf(message, "AT+AB Bypass\r\n");
	HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen(message), 500); //start connection if connection is still available
	for(volatile long i=0; i<1000000; i++);

	sprintf(message, "AT+AB Reset\r\n");
	HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen(message), 500); //reset bt
	for(volatile long i=0; i<80000000; i++);
	*/
	//------------------------------------------------------------------------------------------------------------------------------------------->>>>>>>>>>>>

	UNUSED(message);
}
