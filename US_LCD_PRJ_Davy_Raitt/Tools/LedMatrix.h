/*
 * LedMatrix.h
 *
 * Created: 24-3-2021 11:49:23
 *  Author: Davy
 */ 

#ifndef LEDMATRIX_H
#define LEDMATRIX_H

#include <avr/io.h>
#include <util/delay.h>

void twi_init(void);
void twi_start(void);
void twi_stop(void);
void twi_tx(unsigned char data);
void initHT16K22();
void setMatrixDotOff(unsigned char addres);
void setMatrixDotOn(unsigned char addres);

#endif