#include "serial_lib.h"
#include "main.h"

void Button_init(void)
{
		GPIOC_CRH &= 0xFF0FFFFF;
		GPIOC_CRH |= 0x00400000;
}

void Cyclic_Start(const unsigned short PERIOD)
{
	RCC_APB1ENR |= 0x00000001;
	TIM2_CR1 = 0;
	TIM2_CNT =0;
	if(PERIOD >1)
	{
		TIM2_PSC =  7999;
		TIM2_ARR =(PERIOD-1);
	}
	else
	{
		TIM2_PSC =  799;
		TIM2_ARR =9;			
	}
	TIM2_CR1 = 0x0001;
}
void Cyclic_Wait(void)
{
	while((TIM2_SR & 0x00000001)==0)
	{
	}
	TIM2_SR = 0;
}

void Bpressed(int counter)
{
		counter++;
		Serial_Send_String("Pressed = "+counter,20);
	
}
void BRelease(int counter)
{
		// button in release state
		Serial_Send_String("Released"+counter,20);
	
}

int main(void)
{
	int counter = 0;
	
	Button_init();
	Serial_Init(9600);
	Cyclic_Start(1000);
	while(1)
	{
			
	if((GPIOC_IDR & (0x00002000)) == 0)
	{
		BRelease(counter);
	}
	else
	{
		Bpressed(counter);
	}
		
		Serial_Update();
		Cyclic_Wait();
	
	
	}
	return(1);
}

void SystemInit(void)
{
	
}