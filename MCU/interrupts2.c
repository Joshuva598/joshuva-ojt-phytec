//Interrupts from two input pins

#include "stm32f4xx.h"

void delayMs(int n);

int main(void) {
	__disable_irq(); /* global disable IRQs */
	RCC->AHB1ENR |= 4; /* enable GPIOC clock */ 
	RCC->AHB1ENR |= 2; /*enable GPIOB clock */ 
	RCC->AHB1ENR |= 1; /* enable GPIOA clock */
	RCC->APB2ENR |= 0x4000; /* enable SYSCFG clock */
/* configure PA5 for LED */
	GPIOA->MODER &= ~0x00000C00; /* clear pin mode */ 
	GPIOA->MODER |=0x00000400; /* set pin to output mode *//* configure PC13 for push button interrupt */
	GPIOC->MODER &= ~0x0C000000; /* clear pin mode to input mode */
	SYSCFG->EXTICR[3] &= ~0x00F0; /* clear port selection for EXTI13 */
	SYSCFG->EXTICR[3] |= 0x0020; /* select port C for EXTI13 */
	EXTI->IMR |= 0x2000; /* unmask EXTI13 */
	EXTI->FTSR |= 0x2000; /* select falling edge trigger */
/* configure PB10 for interrupt */
	GPIOB->MODER &= ~0x00030000; /* clear pin mode to input mode */
	GPIOB->PUPDR &= ~0x00300000;
	GPIOB->PUPDR |= 0x00100000; /* enable pull up resistor */
	SYSCFG->EXTICR[2] &= ~0x0F00; /* clear port selection for EXTI10 */
	SYSCFG->EXTICR[2] |= 0x0100; /* select port B for EXTI10 */
	EXTI->IMR |= 0x0400; /* unmask EXTI10 */
	EXTI->FTSR |= 0x0400; /* select falling edge trigger */
	NVIC_EnableIRQ(EXTI15_10_IRQn); /* enable interrupt in NVIC */
	__enable_irq(); /* global enable IRQs */
	while(1) { }
}

void EXTI15_10_IRQHandler(void) {
	
	if (EXTI->PR == 0x2000) { /* interrupt from PC13 */ 
	GPIOA->BSRR =0x00000020; /* turn on green LED */ 
	delayMs(250);
	GPIOA->BSRR = 0x00200000; /* turn off green LED */ 
	delayMs(250);
	GPIOA->BSRR = 0x00000020; /* turn on green LED */ 
	delayMs(250);
	GPIOA->BSRR = 0x00200000; /* turn off green LED */ 
	delayMs(250);
	EXTI->PR = 0x2000; /* clear interrupt pending flag */ 
	}
	
	else if (EXTI->PR == 0x0400) { /* interrupt from PB10 */
	GPIOA->BSRR=0x00000020;

	delayMs(250);
	GPIOA->BSRR=0x00200000;
	delayMs(250);
	GPIOA->BSRR=0x00000020;
	delayMs(250);
	GPIOA->BSRR=0x00200000;
	delayMs(250);
	GPIOA->BSRR=0x00000020;
	delayMs(250);
	GPIOA->BSRR=0x00200000;


	EXTI->PR = 0x0400; /* clear interrupt pending flag */ 
	}
}
/* 16 MHz SYSCLK */
void delayMs(int n) {
	int i;
	for (; n > 0; n--)
	for (i = 0; i < 3195; i++) ; 
}
