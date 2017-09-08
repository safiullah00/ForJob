/******************************************************************************
Serial library v2.0

-uses the DMA
******************************************************************************/

#include "main.h"
#include "serial_lib.h"

static char Serial_tx_buffer_G[SERIAL_TX_BUF_SIZE];
static uint8_t Serial_tx_buffer_in_index_G;
static uint8_t Serial_tx_buffer_out_index_G;
static uint8_t Serial_tx_buffer_count_G;

static char Serial_rx_buffer_G[SERIAL_RX_BUF_SIZE];
static uint8_t Serial_rx_buffer_in_index_G;
static uint8_t Serial_rx_buffer_out_index_G;
static uint8_t Serial_rx_buffer_count_G;


char Serial_Tx_Queue_Write(const char);
char Serial_Tx_Queue_Read(void);
char Serial_Rx_Queue_Write(const char);
char Serial_Rx_Queue_Read(void);

static uint8_t Serial_dma_tx_buffer_G[SERIAL_TX_DMA_BUFF_SIZE];
static uint8_t Serial_dma_rx_buffer_G[SERIAL_RX_DMA_BUFF_SIZE];
static volatile uint16_t Rx_DMA_last_count_G;








void Serial_Init(uint32_t Baud_rate)
{
	uint32_t i;
	uint32_t Temp_1, Temp_2;

	//initialisation of the queue and buffer
	for(i = 0; i < SERIAL_TX_BUF_SIZE; i++)
	{
		Serial_tx_buffer_G[i] = 0;
	}
	Serial_tx_buffer_in_index_G = 0;
	Serial_tx_buffer_out_index_G = 0;
	Serial_tx_buffer_count_G = 0;
	//initialisation of the queue and buffer
	for(i = 0; i < SERIAL_RX_BUF_SIZE; i++)
	{
		Serial_rx_buffer_G[i] = 0;
	}
	Serial_rx_buffer_in_index_G = 0;
	Serial_rx_buffer_out_index_G = 0;
	Serial_rx_buffer_count_G = 0;

	Temp_1 = ((APB1_FREQ / Baud_rate)/16);
	Temp_2 = ((APB1_FREQ / Baud_rate)) - Temp_1*16;
	//Enable RCC
	RCC_APB1ENR |= 0x00020000;//USART 2
	RCC_APB2ENR |= 0x00000004;//Port A
	RCC_AHBENR |= 0x00000001;//DMA
	
	//Configure pins
	GPIOA_CRL &= 0xFFFF00FF;
	GPIOA_CRL |= 0x00004A00;	//Port A.2 as 2Mhz Push pull (alternate) and A.3 as floating input
	
	//Configure the USART
	USART2_CR1 = 0x0000000C;	//8 bit data
	USART2_CR2 = 0x00000000;	//1 stop bit
	USART2_CR3 = 0x000000C0;	//enable DMA for Tx and Rx
	
	USART2_BRR = (Temp_1<<4)|Temp_2;

	//rx dma
	DMA_CCR6 = 0x0020A0;
	DMA_CNDTR6 = SERIAL_RX_DMA_BUFF_SIZE;
	DMA_CPAR6 = (uint32_t)&USART2_DR;
	DMA_CMAR6 = (uint32_t)&Serial_dma_rx_buffer_G[0];

	//tx dma
	DMA_CCR7 = 0x001090;
	DMA_CNDTR7 = 0;
	DMA_CPAR7 = (uint32_t)&USART2_DR;
	DMA_CMAR7 = (uint32_t)&Serial_dma_tx_buffer_G[0];
	
	Rx_DMA_last_count_G = DMA_CNDTR6;


	DMA_CCR6 |= 0x0001;
	DMA_CCR7 |= 0x0001;

	USART2_CR1 |= 0x00002000;	//Enable the USART
	Serial_Send_String("\r\nLink OK\r\n", 12);
	//Serial_Update();

	
	
}

void Serial_Update(void)
{
	uint32_t	i;
	volatile uint16_t Tx_DMA_current_count;
	volatile uint8_t Timeout1 = 1;
	volatile uint16_t Rx_DMA_current_count;

	//check if there is data in tx software buffer
	if(Serial_tx_buffer_count_G > 0)
		{
		//Have data in the software buffer!

		//check if serial DMA tx buffer is empty
		Tx_DMA_current_count = DMA_CNDTR7;
		if(Tx_DMA_current_count == 0)
			{
			//DMA has finished sending the last byte.

			//disable the DMA channel
			DMA_CCR7 &= 0xFFFFFFFE;

			//fill up the DMA buffer
			i = 0;
			while ((i < SERIAL_TX_DMA_BUFF_SIZE) && (Serial_tx_buffer_count_G > 0))
				{
				Serial_dma_tx_buffer_G[i] = Serial_Tx_Queue_Read();
				i++;
				}
			//setup and re-enable the DMA channel
			DMA_CNDTR7 = i;
			if(i>0)
				{
				DMA_CCR7 = 0x001090;
				DMA_CPAR7 = (uint32_t)&USART2_DR;
				DMA_CMAR7 = (uint32_t)&Serial_dma_tx_buffer_G[0];
	
				DMA_CCR7 |= 0x0001;
				}
			}
		}



	
	//check if there is data in RBR FIFO
	Rx_DMA_current_count = DMA_CNDTR6;
	while((Rx_DMA_last_count_G != Rx_DMA_current_count) && (++Timeout1))
		{
		//if yes store data into software buffer + set flag....
		Serial_Rx_Queue_Write(Serial_dma_rx_buffer_G[SERIAL_RX_DMA_BUFF_SIZE - Rx_DMA_last_count_G]);
		if(Rx_DMA_last_count_G > 1)
			{
			Rx_DMA_last_count_G--;
			}
		else
			{
			Rx_DMA_last_count_G = SERIAL_RX_DMA_BUFF_SIZE;
			}
		}
}

void Serial_Send_String(char * Data, uint16_t Length)
{
	uint16_t Count = 0;
	
	//loop while there is data to copy
	while(Count < Length)
	{
		if(Data[Count] == '\0')
		{
			//end of string reached. Exit loop.
			break;
		}
		Serial_Tx_Queue_Write(Data[Count]);
		Count++;
	}
}

void Serial_Send_Byte(char Data)
{
	Serial_Tx_Queue_Write(Data);
}


uint16_t Serial_Get_Buffer_Status(void)
{
	return Serial_rx_buffer_count_G;
}

char Serial_Get_Byte(void)
{
	char Return_data;
	if(Serial_rx_buffer_count_G > 0)
	{
		Return_data = Serial_Rx_Queue_Read();
	}
	else
	{
		Return_data = 0;
	}
	return Return_data;
}




char Serial_Tx_Queue_Write(const char DATA)
{
	char Return_value = 1;
	//check if space available
	if(Serial_tx_buffer_count_G < SERIAL_TX_BUF_SIZE)
	{
		Serial_tx_buffer_G[Serial_tx_buffer_in_index_G] = DATA;
		Serial_tx_buffer_in_index_G++;
		if(Serial_tx_buffer_in_index_G >= SERIAL_TX_BUF_SIZE)
		{
			Serial_tx_buffer_in_index_G = 0;
		}
		Serial_tx_buffer_count_G++;
		Return_value = 0;
	}
	return Return_value;
}

char Serial_Tx_Queue_Read(void)
{
	char Return_value = 0;
	//check if data present in queue
	if(Serial_tx_buffer_count_G > 0)
	{
		Return_value = Serial_tx_buffer_G[Serial_tx_buffer_out_index_G];
		Serial_tx_buffer_out_index_G++;
		if(Serial_tx_buffer_out_index_G >= SERIAL_TX_BUF_SIZE)
		{
			Serial_tx_buffer_out_index_G = 0;
		}
		Serial_tx_buffer_count_G--;
	}
	return Return_value;
}

char Serial_Rx_Queue_Write(const char DATA)
{
	char Return_value = 1;
	//check if space available
	if(Serial_rx_buffer_count_G < SERIAL_RX_BUF_SIZE)
	{
		Serial_rx_buffer_G[Serial_rx_buffer_in_index_G] = DATA;
		Serial_rx_buffer_in_index_G++;
		if(Serial_rx_buffer_in_index_G >= SERIAL_RX_BUF_SIZE)
		{
			Serial_rx_buffer_in_index_G = 0;
		}
		Serial_rx_buffer_count_G++;
		Return_value = 0;
	}
	return Return_value;
}

char Serial_Rx_Queue_Read(void)
{
	char Return_value = 0;
	//check if data present in queue
	if(Serial_rx_buffer_count_G > 0)
	{
		Return_value = Serial_rx_buffer_G[Serial_rx_buffer_out_index_G];
		Serial_rx_buffer_out_index_G++;
		if(Serial_rx_buffer_out_index_G >= SERIAL_RX_BUF_SIZE)
		{
			Serial_rx_buffer_out_index_G = 0;
		}
		Serial_rx_buffer_count_G--;
	}
	return Return_value;
}
/*
void Cyclic_Start(const unsigned short PERIOD){
	RCC_APB1ENR |= 0x00000001;
	TIM2_CR1=0;
	TIM2_CNT=0;
	if(PERIOD>1){
		TIM2_PSC=7999;
		TIM2_ARR=(PERIOD-1);
		
	}
	else{
		TIM2_PSC=799;
		TIM2_ARR=9;
	}
	TIM2_CR1= 0X0001;
}

void Cyclic_Wait(void){

	while((TIM2_SR & 0x00000001) == 0){
	}
	TIM2_SR=0;
}
*/