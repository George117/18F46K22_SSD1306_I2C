/*
 * File:   i2c.c
 * Author: georg
 *
 * Created on August 28, 2016, 3:25 PM
 */



#define _XTAL_FREQ 64000000
#include <xc.h>
#include "i2c.h"



/////////////////////////////I2C/////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void I2C_Master_Init(unsigned long c)
{
    SSPCON1 = 0b00101000;
    SSPCON2 = 0x00;
    SSPADD = (_XTAL_FREQ/(4*c))-1;
    SSPSTAT = 0x00;
    TRISCbits.TRISC3=1;
    TRISCbits.TRISC4=1;
}
////////////////////////////////////////////////////////////////////////////////
void I2C_Master_Wait()
{
   while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));
   // while(PIR1bits.SSPIF==0);
  //  PIR1bits.SSPIF=1;
}
////////////////////////////////////////////////////////////////////////////////
void I2C_Master_Start()
{
    I2C_Master_Wait();
    SSPCON2bits.SEN = 1;
}
////////////////////////////////////////////////////////////////////////////////
void I2C_Master_RepeatedStart()
{
    I2C_Master_Wait();
    SSPCON2bits.RSEN = 1;
}
////////////////////////////////////////////////////////////////////////////////
void I2C_Master_Stop()
{
    I2C_Master_Wait();
    SSPCON2bits.PEN = 1;
}
////////////////////////////////////////////////////////////////////////////////
void I2C_Master_Write(unsigned d)
{
    I2C_Master_Wait();
    SSPBUF = d;
}
////////////////////////////////////////////////////////////////////////////////
void I2C_Write_Display(unsigned d)
{
    I2C_Master_Wait();
    SSPBUF = d;
}
////////////////////////////////////////////////////////////////////////////////
unsigned short I2C_Master_Read(unsigned short a)
{
    unsigned short temp;
    I2C_Master_Wait();
    SSP1CON2bits.RCEN = 1;
    I2C_Master_Wait();
    temp = SSPBUF;
    I2C_Master_Wait();
    SSP1CON2bits.ACKDT = (a)?0:1;
    SSP1CON2bits.ACKEN = 1;
    return temp;
}
////////////////////////////////////////////////////////////////////////////////
