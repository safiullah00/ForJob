#define RCC_APB2ENR  (*((volatile unsigned long*) 0x40021018))
#define RCC_APB1ENR  (*((volatile unsigned long*) 0x4002101C))

#define GPIOA_CRL    (*((volatile unsigned long*) 0x40010800))
#define GPIOA_BSRR   (*((volatile unsigned long*) 0x40010810))	

#define TIM2_CR1     (*((volatile unsigned long*) 0x40000000))
#define TIM2_CNT     (*((volatile unsigned long*) 0x40000024))
#define TIM2_PSC     (*((volatile unsigned long*) 0x40000028))
#define TIM2_ARR     (*((volatile unsigned long*) 0x4000002C))
#define TIM2_SR      (*((volatile unsigned long*) 0x40000010))


void Cyclic_Start(const unsigned short PERIOD)
{
	RCC_APB1ENR |= 0x00000001;
	TIM2_CR1 =0;
	TIM2_CNT =0;
	
	if(PERIOD >1)
	{
		TIM2_PSC = 7999;
		TIM2_ARR = (PERIOD-1);
	}
else
{
	TIM2_PSC =799;
	TIM2_ARR = 9;
	
}	
TIM2_CR1 =0x001;
}


void Cyclic_Wait(void)
{
		while((TIM2_SR & 0x00000001) == 0)
		{
			
		}
		TIM2_SR = 0;
}


void LED_Init(void)
{
	RCC_APB2ENR |= 0x00000004; GPIOA_CRL &= 0xFFFFFF0F;
	GPIOA_CRL |= 0x00000020;
}

void LED_On(void)
{
	GPIOA_BSRR = 0x00000002;
}

void LED_Off(void)
{
	GPIOA_BSRR = 0x00020000;
}

void LED_Toggle(void)
{
	static unsigned char LED_state = 0;
	if (LED_state == 0)
	{
		LED_state = 1;
		LED_On();
	}
	else
	{
		LED_state =0;
		LED_Off();
		
	}
}


int main(void)
{
	LED_Init();
	Cyclic_Start(150);
	
	while(1)
	{
		LED_Toggle();
		Cyclic_Wait();
		
	}
	return (1);
}

void SystemInit(void)
{

}