#include "main.h"
#ifndef _SERIAL_LIB_H_
#define _SERIAL_LIB_H_

#define SERIAL_TX_BUF_SIZE	200
#define SERIAL_RX_BUF_SIZE	200

#define SERIAL_TX_DMA_BUFF_SIZE	32
#define SERIAL_RX_DMA_BUFF_SIZE	100


void Serial_Init(uint32_t);
void Serial_Update(void);
void Serial_Send_String(char *,unsigned int uint16_t);
void Serial_Send_Byte(char);
uint16_t Serial_Get_Buffer_Status(void);
char Serial_Get_Byte(void);



#endif
