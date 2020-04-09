#ifndef ADS1220_INTERFACE_H
#define ADS1220_INTERFACE_H

void reset(void);
int readConfiguration(void);
uint32_t ads1220_read_data();

void ads1220_object_init();


#endif // ADS1220_INTERFACE_H
