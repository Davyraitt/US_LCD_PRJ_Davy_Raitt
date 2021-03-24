/*
 * LedMatrix.c
 *
 * Created: 24-3-2021 11:49:14
 *  Author: Davy
 */ 

#include "LedMatrix.h"

void twi_init(void) // Init AVR TWI interface and set bitrate
{
	TWSR = 0;
	TWBR = 32;	 // TWI clock set to 100kHz, prescaler = 0
}


void twi_start(void) // //Generate TWI start condition
{
	TWCR = (0x80 | 0x20 | 0x04);
	while( 0x00 == (TWCR & 0x80) );
}


void twi_stop(void) // Generate TWI stop condition
{
	TWCR = (0x80 | 0x10 | 0x04);
}


void twi_tx(unsigned char data) //transmit 8 bits data
{
	TWDR = data;
	TWCR = (0x80 | 0x04);
	while( 0 == (TWCR & 0x80) );
}

void initHT16K22() // Init AVR TWI interface and set bitrate
{
	// Init HT16K22. Page 32 datasheet
	twi_start();
	twi_tx(0xE0);	// Display I2C addres + R/W bit
	twi_tx(0x21);	// Internal osc on (page 10 HT16K33)
	twi_stop();

	twi_start();
	twi_tx(0xE0);	// Display I2C address + R/W bit
	twi_tx(0xA0);	// HT16K33 pins all output
	twi_stop();

	twi_start();
	twi_tx(0xE0);	// Display I2C address + R/W bit
	twi_tx(0xE3);	// Display Dimming 4/16 duty cycle
	twi_stop();

	twi_start();
	twi_tx(0xE0);	// Display I2C address + R/W bit
	twi_tx(0x81);	// Display OFF - Blink On
	twi_stop();
}

void setMatrixDotOff(unsigned char addres){
	//page 28 of the datasheet (https://cdn-shop.adafruit.com/datasheets/ht16K33v110.pdf)
	//contains an example command
	//A byte write operation requires a START condition, slave address with R/W bit, a valid Command
	//code / Register address, a Data and a STOP condition.
	
	twi_start(); // START condition
	twi_tx(0xE0);	// Display I2C addres + R/W bit
	twi_tx(addres);	// Address
	
	//? {0}: Display off
	//? {1}: Display on
	twi_tx(0x00);	// data
	twi_stop(); // Sending stop condition
}

void setMatrixDotOn(unsigned char addres){
	//page 28 of the datasheet (https://cdn-shop.adafruit.com/datasheets/ht16K33v110.pdf)
	//contains an example command
	//A byte write operation requires a START condition, slave address with R/W bit, a valid Command
	//code / Register address, a Data and a STOP condition.
	
	twi_start(); // START condition
	twi_tx(0xE0);	// Display I2C addres + R/W bit
	twi_tx(addres);	// Address
	
	//? {0}: Display off
	//? {1}: Display on
	twi_tx(0x01);	// data
	twi_stop(); // Sending stop condition
}

