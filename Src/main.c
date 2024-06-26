/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Rohan Guraja
 * @brief          : Program to view HSI using MCO on PA8 of STM32f303RE
 ******************************************************************************
*/

#include <stdint.h>

#define RCC_BASE_ADDR			0x40021000UL
#define RCC_CFGR_OFFSET_ADDR	0x04UL
#define RCC_CGGR_ADDR			(RCC_BASE_ADDR + RCC_CFGR_OFFSET_ADDR)

#define RCC_AHBENR_OFFSET_ADDR	0x14
#define RCC_AHBENR_ADDR			(RCC_BASE_ADDR + RCC_AHBENR_OFFSET_ADDR)

#define GPIOA_BASE_ADDR				0x48000000UL
#define GPIOA_MODER_OFFSET_ADDR		0x00UL
#define GPIOA_MODER_ADDR			(GPIOA_BASE_ADDR + GPIOA_MODER_OFFSET_ADDR)

#define GPIOA_AFRH_OFFSET			0x24UL
#define GPIOA_AFRH_ADDR				(GPIOA_BASE_ADDR + GPIOA_AFRH_OFFSET)

int main(void)
{
	//RCC register definitions to set HSI and GPIO
	uint32_t *pRCC_CFGR = (uint32_t *)RCC_CGGR_ADDR;
	uint32_t *pRCC_AHBENR = (uint32_t *)RCC_AHBENR_ADDR;

	//GPIO registers used to set
	uint32_t *pGPIOA_MODER = (uint32_t *)GPIOA_MODER_ADDR;
	uint32_t *pGPIOA_AFRH = (uint32_t *)GPIOA_AFRH_ADDR;

	//set RCC_CFGR Bits 26:24 to 101 // set MCO source to HSI
	*pRCC_CFGR |= (1<<24) | (1<<26);
	*pRCC_CFGR &= ~(1<<25);

	//clear bits 30:28 without affecting the other bits // set MCO divider to 0 - first set bits 30:28 then not them to change them to 0 and all other bits to 1 and and them to original
	*pRCC_CFGR &= ~((1<<30) | (1<<29) | (1<<28));

	//SET RCC_AHBENR BIT 17 TO 1 // enabling AHB clock
	*pRCC_AHBENR |= (1<<17);

	//Set GPIO_MODER bit 17:16 to 10 // Set PA8 to AF
	*pGPIOA_MODER |= (1<<17);
	*pGPIOA_MODER &= ~(1<<16);

	// set GPIO_AFRH bit 3:0 to 0000 //set PA8 AF to MCO
	*pGPIOA_AFRH &= ~((1<<0) | (1<<1) | (1<<2) | (1<<3));

    /*Loop forever */
	for(;;);
}
