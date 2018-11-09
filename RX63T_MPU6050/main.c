/************************************************************************/
/*																		*/
/*  FILE        :	main.c										*/
/*  DATE        :	JUN. 11, 2013										*/
/*  DESCRIPTION :	Main Program										*/
/*  CPU TYPE    :   Renesas RX63TH										*/
/*	H/W Platform:	QB-RX63TH-TB										*/
/*  Programmer  :	Ziyuan Chen (VICTRON TECHNOLOGY, TAIWAN)			*/
/*  NOTE:THIS IS A TYPICAL EXAMPLE.										*/
/*                                                                      */
/************************************************************************/

/***********************************************************************
Includes <System Includes> , "Project Includes"
***********************************************************************/
#include "typedefine.h"
#include "iodefine.h"
#include <stdio.h>			// Used for printf()
#include <machine.h>
#include <riic.h>
#include <uart.h>

#define	SMPLRT_DIV		0x19
#define	CONFIG			0x1A
#define	GYRO_CONFIG		0x1B
#define	ACCEL_CONFIG	0x1C
#define	ACCEL_XOUT_H	0x3B
#define	ACCEL_XOUT_L	0x3C
#define	ACCEL_YOUT_H	0x3D
#define	ACCEL_YOUT_L	0x3E
#define	ACCEL_ZOUT_H	0x3F
#define	ACCEL_ZOUT_L	0x40
#define	TEMP_OUT_H		0x41
#define	TEMP_OUT_L		0x42
#define	GYRO_XOUT_H		0x43
#define	GYRO_XOUT_L		0x44	
#define	GYRO_YOUT_H		0x45
#define	GYRO_YOUT_L		0x46
#define	GYRO_ZOUT_H		0x47
#define	GYRO_ZOUT_L		0x48
#define	PWR_MGMT_1		0x6B
#define	WHO_AM_I		0x75
#define	SlaveAddress	0x68


#ifdef __cplusplus
//#include <ios>					// Remove the comment when you use ios
//_SINT ios_base::Init::init_cnt;	// Remove the comment when you use ios
#endif

/***********************************************************************
  Function prototype declaration                                     
***********************************************************************/
void main(void);
void InitMPU6050(void);
void Single_WriteI2C(unsigned char ,unsigned char );
unsigned char Single_ReadI2C(unsigned char );
void GetGyroData(short *);
void GetAccelData(short *);

#ifdef __cplusplus
extern "C" {
void abort(void);
}
#endif

/****************************************************************************
* Outline      : Main
* Description  : Hardware setting and CPU sleep
*****************************************************************************/
void main(void)
{
	// Sensor data.
	// 	data[0] : X axis
	// 	data[1] : Y axis
	// 	data[2] : Z axis
	short data[3];
	
	// UART initialize. BAUD_RATE 115200, 8-bit data, no parity, 1 stop bit.
    UART_Create();
	// IIC initialize and IIC interrupt enable.
	IIC_Create();
	// MPU6050 initialize.
	InitMPU6050();

	while(1)
	{
		// Get Gyro data.
		GetGyroData(data);
		// data output.
		printf("%d, %d, %d\r\n",data[0],data[1],data[2]);
		I2C_Delay_ms(10); 
	}
}

void InitMPU6050(void)
{
	Single_WriteI2C(PWR_MGMT_1, 0x00);
	Single_WriteI2C(SMPLRT_DIV, 0x07);
	Single_WriteI2C(CONFIG,		0x06);
	Single_WriteI2C(GYRO_CONFIG,0x18);
	Single_WriteI2C(ACCEL_CONFIG,0x01);
}

void Single_WriteI2C(unsigned char REG_Address,unsigned char REG_data)
{
    unsigned char data[1];
 
	data[0] = REG_data;
	I2C_writeBytesToAddress(SlaveAddress, REG_Address, 1, data);
}

unsigned char Single_ReadI2C(unsigned char REG_Address)
{
	unsigned char REG_data;

	I2C_readBytesFromAddress(SlaveAddress, REG_Address, 1, &REG_data);
	return REG_data;
}

void GetGyroData(short *data)
{
	unsigned char tmp[6];
	I2C_readBytesFromAddress(SlaveAddress, GYRO_XOUT_H, 6, tmp);
	data[0] = (tmp[0] << 8) | tmp[1];
    data[1] = (tmp[2] << 8) | tmp[3];
    data[2] = (tmp[4] << 8) | tmp[5];
}

void GetAccelData(short *data)
{
	unsigned char tmp[6];
	I2C_readBytesFromAddress(SlaveAddress, ACCEL_XOUT_H, 6, tmp);
	data[0] = (tmp[0] << 8) | tmp[1];
    data[1] = (tmp[2] << 8) | tmp[3];
    data[2] = (tmp[4] << 8) | tmp[5];
}

#ifdef __cplusplus
void abort(void)
{

}
#endif
