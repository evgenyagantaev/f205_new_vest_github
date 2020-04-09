#ifndef AD7792_INTERFACE_H
#define AD7792_INTERFACE_H

void ad7792_reset(void);
int ad7792_readMode();
uint16_t ad7792_read_data();

void ad7792_object_init();


#endif // AD7792_INTERFACE_H
