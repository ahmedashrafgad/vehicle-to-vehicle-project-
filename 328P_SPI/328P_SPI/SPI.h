/*
 * SPI.h
 *
 * Created: 12/06/2018 08:42:21 م
 *  Author: Ahmed Manzpur
 */ 


#ifndef SPI_H_
#define SPI_H_
#include <avr/io.h>

void spiInitMaster(void);
void spiInitSlave(void);
char spiReceive(void);
void spiTransmit(char dataOut, int slavePin);


#endif /* SPI_H_ */