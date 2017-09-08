/*------------------------------------------------------------------*-
   Main.H (v1.00)
  ------------------------------------------------------------------
   'Project Header' for project _________________
-*------------------------------------------------------------------*/
#ifndef _MAIN_H
#define _MAIN_H

//------------------------------------------------------------------
// WILL NEED TO EDIT THIS SECTION FOR EVERY PROJECT
//------------------------------------------------------------------
// Must ensure all used registers are defined / included here
#define RCC_AHBENR		( * ((volatile unsigned long*) 0x40021014))
#define RCC_APB2ENR		( * ((volatile unsigned long*) 0x40021018))
#define RCC_APB1ENR		( * ((volatile unsigned long*) 0x4002101C))

#define GPIOA_CRL			( * ((volatile unsigned long*) 0x40010800))
#define GPIOA_CRH			( * ((volatile unsigned long*) 0x40010804))
#define GPIOA_IDR			( * ((volatile unsigned long*) 0x40010808))
#define GPIOA_ODR			( * ((volatile unsigned long*) 0x4001080C))
#define GPIOA_BSRR		( * ((volatile unsigned long*) 0x40010810))
#define GPIOA_BRR			( * ((volatile unsigned long*) 0x40010814))
#define GPIOA_LCKR		( * ((volatile unsigned long*) 0x40010818))
	
#define GPIOB_CRL     ( * ((volatile unsigned long*) 0x40010C00))
	
#define ADC_SMPR1     ( * ((volatile unsigned long*) 0x4001280C))
#define ADC_SMPR2     ( * ((volatile unsigned long*) 0x40012410))
#define ADC_CR2       ( * ((volatile unsigned long*) 0x40012408))
#define ADC_CR1       ( * ((volatile unsigned long*) 0x40012804))
#define ADC_SQR3      ( * ((volatile unsigned long*) 0x40012434))
#define ADC_SR        ( * ((volatile unsigned long*) 0x40012400))
#define ADC_DR        ( * ((volatile unsigned long*) 0x4001244C))
//#define ADC_SQR3       ( * ((volatile unsigned long*) 0x40012834))


#define GPIOC_CRL			( * ((volatile unsigned long*) 0x40011000))
#define GPIOC_CRH			( * ((volatile unsigned long*) 0x40011004))
#define GPIOC_IDR			( * ((volatile unsigned long*) 0x40011008))
#define GPIOC_ODR			( * ((volatile unsigned long*) 0x4001100C))
#define GPIOC_BSRR		( * ((volatile unsigned long*) 0x40011010))
#define GPIOC_BRR			( * ((volatile unsigned long*) 0x40011014))
#define GPIOC_LCKR		( * ((volatile unsigned long*) 0x40011018))

#define TIM2_CR1			( * ((volatile unsigned long*) 0x40000000))
#define TIM2_CNT			( * ((volatile unsigned long*) 0x40000024))
#define TIM2_PSC			( * ((volatile unsigned long*) 0x40000028))
#define TIM2_ARR			( * ((volatile unsigned long*) 0x4000002C))
#define TIM2_SR				( * ((volatile unsigned long*) 0x40000010))

#define TIM3_CR1			( * ((volatile unsigned long*) 0x40000400))
#define TIM3_CNT			( * ((volatile unsigned long*) 0x40000424))
#define TIM3_PSC			( * ((volatile unsigned long*) 0x40000428))
#define TIM3_ARR			( * ((volatile unsigned long*) 0x4000042C))
#define TIM3_SR				( * ((volatile unsigned long*) 0x40000410))


#define USART2_SR			( * ((volatile unsigned long*) 0x40004400))
#define USART2_DR			( * ((volatile unsigned long*) 0x40004404))
#define USART2_BRR		( * ((volatile unsigned long*) 0x40004408))
#define USART2_CR1		( * ((volatile unsigned long*) 0x4000440C))
#define USART2_CR2		( * ((volatile unsigned long*) 0x40004410))
#define USART2_CR3		( * ((volatile unsigned long*) 0x40004414))
#define USART2_GTPR		( * ((volatile unsigned long*) 0x40004418))

#define DMA_ISR				( * ((volatile unsigned long*) 0x40020000))
#define DMA_IFCR			( * ((volatile unsigned long*) 0x40020004))

#define DMA_CCR1			( * ((volatile unsigned long*) 0x40020008))
#define DMA_CNDTR1			( * ((volatile unsigned long*) 0x4002000C))
#define DMA_CPAR1			( * ((volatile unsigned long*) 0x40020010))
#define DMA_CMAR1			( * ((volatile unsigned long*) 0x40020014))

#define DMA_CCR2			( * ((volatile unsigned long*) 0x4002001C))
#define DMA_CNDTR2			( * ((volatile unsigned long*) 0x40020020))
#define DMA_CPAR2			( * ((volatile unsigned long*) 0x40020024))
#define DMA_CMAR2			( * ((volatile unsigned long*) 0x40020028))

#define DMA_CCR3			( * ((volatile unsigned long*) 0x40020030))
#define DMA_CNDTR3			( * ((volatile unsigned long*) 0x40020034))
#define DMA_CPAR3			( * ((volatile unsigned long*) 0x40020038))
#define DMA_CMAR3			( * ((volatile unsigned long*) 0x4002003C))

#define DMA_CCR4			( * ((volatile unsigned long*) 0x40020044))
#define DMA_CNDTR4			( * ((volatile unsigned long*) 0x40020048))
#define DMA_CPAR4			( * ((volatile unsigned long*) 0x4002004C))
#define DMA_CMAR4			( * ((volatile unsigned long*) 0x40020050))

#define DMA_CCR5			( * ((volatile unsigned long*) 0x40020058))
#define DMA_CNDTR5			( * ((volatile unsigned long*) 0x4002005C))
#define DMA_CPAR5			( * ((volatile unsigned long*) 0x40020060))
#define DMA_CMAR5			( * ((volatile unsigned long*) 0x40020064))

#define DMA_CCR6			( * ((volatile unsigned long*) 0x4002006C))
#define DMA_CNDTR6			( * ((volatile unsigned long*) 0x40020070))
#define DMA_CPAR6			( * ((volatile unsigned long*) 0x40020074))
#define DMA_CMAR6			( * ((volatile unsigned long*) 0x40020078))

#define DMA_CCR7			( * ((volatile unsigned long*) 0x40020080))
#define DMA_CNDTR7			( * ((volatile unsigned long*) 0x40020084))
#define DMA_CPAR7			( * ((volatile unsigned long*) 0x40020088))
#define DMA_CMAR7			( * ((volatile unsigned long*) 0x4002008C))


// Clock frequencies
#define HSE_FREQ (8000000UL)
#define HSI_FREQ (8000000UL)
#define PLL_MUL  (3)

//Uncomment the correct line based on the source for the PLL
#define PLL_FREQ (HSE_FREQ * PLL_MUL)
// #define PLL_FREQ ((HSI_FREQ /2 )* PLL_MUL)

// Select the correct frequency as the SYS_CLK (i.e. HSE_FREQ, HSI_FREQ or PLL_FREQ
#define SYS_CLK  HSI_FREQ

#define AHB_DIV  (1)
#define AHB_FREQ (SYS_CLK / AHB_DIV)
#define APB1_DIV  (1)
#define APB1_FREQ (AHB_FREQ / APB1_DIV)
#define APB2_DIV  (1)
#define APB2_FREQ (AHB_FREQ / APB1_DIV)

#if APB1_DIV == 1
#define APB1_TIMx_FREQ (APB1_FREQ)
#else
#define APB1_TIMx_FREQ (APB1_FREQ * 2)
#endif

#if APB2_DIV == 1
#define APB2_TIMx_FREQ (APB2_FREQ)
#else
#define APB2_TIMx_FREQ (APB2_FREQ * 2)
#endif

//------------------------------------------------------------------
// SHOULD NOT NEED TO EDIT THE SECTIONS BELOW
//------------------------------------------------------------------
// Typedefs
typedef unsigned char  uint8_t;
typedef unsigned int uint16_t;
typedef unsigned int   uint32_t;
typedef char           int8_t;
typedef short          int16_t;
typedef int            int32_t;

#endif
/*------------------------------------------------------------------*-
  ---- END OF FILE -------------------------------------------------
-*------------------------------------------------------------------*/

