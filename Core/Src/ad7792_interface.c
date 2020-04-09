#include "ad7792_obj.h"
#include "ad7792_interface.h"

#include "usart.h"
#include "spi.h"



// Function resets ad7792
void ad7792_reset()
{
	volatile long i;

	//In situations where the interface sequence is lost, a write operation of at least 32 serial clock cycles with DIN high
	//returns the ADC to this default state by resetting the entire part.
	// first: reset adc (set mosi line high for more then 32 clk cycles)
	for (i=0;i<10;i++)
	{
		while ((SPI2->SR & SPI_FLAG_TXE) == RESET );
		SPI2->DR=0xFF;
	}

	for(i=0; i<1500000; i++);

	// Now adc waits a comm register write operation and all on-chip registers
	// are in their power-on state

	// *** configure configuration register:
	// gain = 4  00000<010> external reference <0>00 unbuffered mode <0>0
	// channel 1 <000>
	// <0000001000000000> = 0x0200

	// (0<0><010><0>00)0x10 - write in the configuration register
	//(<0000001000000000> = 0x0200)
	while ((SPI2->SR & SPI_FLAG_TXE) == RESET );
	SPI2->DR=0x10;
	while ((SPI2->SR & SPI_FLAG_TXE) == RESET );
	SPI2->DR=0x02;
	while ((SPI2->SR & SPI_FLAG_TXE) == RESET );
	SPI2->DR=0x00;

	// *** configure mode register:
	// continuous conversion mode <000>00000 internal clock <00>00 470 Hz <0001>
	// <0000000000000001> = 0x0001

	// (0<0><001><0>00)0x08 - write in the mode register
	//(value = <0000000000000001> = 0x0001)
	while ((SPI2->SR & SPI_FLAG_TXE) == RESET );
	SPI2->DR=0x08;
	while ((SPI2->SR & SPI_FLAG_TXE) == RESET );
	SPI2->DR=0x00;
	while ((SPI2->SR & SPI_FLAG_TXE) == RESET );
	SPI2->DR=0x01;  // debug conversion rate = 470 Hz
	//SPI2->DR=0x02; // debug conversion rate = 242 Hz

	for(i=0; i<1500000; i++);

}//end reset

// Function reads and checks id register
int ad7792_readMode()
{
	uint32_t adResponce;
	// write to the communication register <01001000>
	// the next operation will be a read from mode register
	while ((SPI2->SR & SPI_FLAG_TXE) == RESET );
	SPI2->DR=0x48;
	while ((SPI2->SR & SPI_FLAG_TXE) == RESET );
	// fictious write in spi (just to start a clock and read mode register h byte
	SPI2->DR=0x55;
	while ((SPI2->SR & SPI_FLAG_RXNE) == RESET);
	adResponce=SPI2->DR;
	// fictious write in spi (just to start a clock and read mode register l byte
	SPI2->DR=0x55;
	while ((SPI2->SR & SPI_FLAG_RXNE) == RESET);
	adResponce=SPI2->DR;

	// check the value
	if((uint8_t)adResponce == 0x02) // we have got a correct interface
	 return 0; // ok
	else
	 return 1; // id
}//end readMode




void ad7792_object_init()
{
	// turn on analog circuit
	HAL_GPIO_WritePin(analog_on_GPIO_Port, analog_on_Pin, GPIO_PIN_SET);

	ad7792_reset();

	//if(ad7792_readMode())
	//	while(1);  // no correct configuration
}

uint16_t ad7792_read_data()
{

	uint16_t res=0;
	uint16_t Conv;

	// read data from adc via spi

	while((GPIOB->IDR & GPIO_PIN_14) != (uint32_t)RESET);

	if ((SPI2->SR & SPI_FLAG_RXNE) != RESET )
	res=SPI2->DR;
	// wait for spi transmitter readiness
	while ((SPI2->SR & SPI_FLAG_TXE) == RESET );
	SPI2->DR=0x58;
	// wait while a transmission complete
	while ((SPI2->SR & SPI_FLAG_RXNE) == RESET );
	res=SPI2->DR;

	// wait for spi transmitter readiness
	while ((SPI2->SR & SPI_FLAG_TXE) == RESET );
	SPI2->DR=0xFF;
	while ((SPI2->SR & SPI_FLAG_RXNE) == RESET );
	res=SPI2->DR;
	Conv=(uint16_t)res;

	// wait for spi transmitter readiness
	while ((SPI2->SR & SPI_FLAG_TXE) == RESET );
	SPI2->DR=0xFF;
	while ((SPI2->SR & SPI_FLAG_RXNE) == RESET );
	res=SPI2->DR;
	Conv<<=8;
	Conv|=((uint16_t)res & 0x00ff);

	return Conv;

}

