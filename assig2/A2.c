#define RCC_APB2ENR (*((volatile unsigned long*)0x40021018))
#define RCC_APB1ENR (*((volatile unsigned long*)0x4002101C))
#define GPIOA_CRL (*((volatile unsigned long*)0x40010800))
#define GPIOA_BSRR (*((volatile unsigned long*)0x40010810))
#define TIM2_CR1  (*((volatile unsigned long*)0x40000000))

#define TIM2_CNT (*((volatile unsigned long*)0x40000024))
#define TIM2_PSC (*((volatile unsigned long*)0x40000028))
#define TIM2_ARR (*((volatile unsigned long*)0x4000002C))
#define TIM2_SR  (*((volatile unsigned long*)0x40000010))
void cycle_start(const unsigned short PERIOD)
{
RCC_APB1ENR |=0x00000001;
	TIM2_CR1=0;
	TIM2_CNT=0;
	if(PERIOD>1)
	{
	TIM2_PSC=7999;
		TIM2_ARR=(PERIOD-1);
	}
	else
	{
	TIM2_PSC=799;
		TIM2_ARR=9;
	}
	TIM2_CR1=0x0001;
}

void cycle_wait(void)
{
while((TIM2_SR & 0x00000001) ==0)
{

}
TIM2_SR=0;
}

void led_init(void)
{
RCC_APB2ENR |=0x00000004;
	GPIOA_CRL &=0xFFFFF0FF;
	GPIOA_CRL &=0x00000200;
}

void led_on(void)
{
GPIOA_BSRR=0x0000004;
}

void led_off(void)
{
GPIOA_BSRR=0x00040000;
}
void led_toggle(void)
{
static unsigned char led_state=0;
	if(led_state==0)
	{
	led_state=1;
		led_on();
		Cyclic_Start(500);
	}
		else
		{
		led_state=0;
		led_off();
		//Cyclic_Start(500);
		}
}
int main(void)
{
	led_init();
	cycle_start(1000);
	while(1)
	{
	led_toggle();
		cycle_wait();
	}
return(1);
}
	void SystemInit(void)
	{
	}