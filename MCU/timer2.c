//Using Timer to measure period and frequency


#include "stm32f4xx.h"

int period;
float frequency;

int main(void) {
	int last = 0;
	int current;
// configure PA5 as output of TIM2 CH1
	RCC->AHB1ENR |= 1; /* enable GPIOA clock */
	GPIOA->MODER &= ~0x00000C00; /* clear pin mode */
	GPIOA->MODER |= 0x00000800; /* set pin to alternate function */
	GPIOA->AFR[0] &= ~0x00F00000; /* clear pin AF bits */ 
	GPIOA->AFR[0]|= 0x00100000; /* set pin to AF1 for TIM2 CH1 */
// configure TIM2 to wrap around at 1 Hz
// and toggle CH1 output when the counter value is 0
	RCC->APB1ENR |= 1; /* enable TIM2 clock */
	TIM2->PSC = 1600 - 1; /* divided by 1600 */
	TIM2->ARR = 3000 - 1; /* divided by 3000 */
	TIM2->CCMR1 = 0x30; /* set output to toggle on match */
	TIM2->CCR1 = 0; /* set match value */
	TIM2->CCER |= 1; /* enable ch 1 compare mode */
	TIM2->CNT = 0; /* clear counter */
	TIM2->CR1 = 1; /* enable TIM2 */
// configure PA6 as input of TIM3 CH1
	RCC->AHB1ENR |= 1; /* enable GPIOA clock */ 
	GPIOA->MODER &=~0x00003000; /* clear pin mode */
	GPIOA->MODER |= 0x00002000; /* set pin to alternate function */
	GPIOA->AFR[0] &= ~0x0F000000; /* clear pin AF bits */ 
	GPIOA->AFR[0]|= 0x02000000; /* set pin to AF2 for TIM3 CH1 */
// configure TIM3 to do input capture with prescaler ...
	RCC->APB1ENR |= 2; /* enable TIM3 clock */
	TIM3->PSC = 16000 - 1; /* divided by 16000 */
	TIM3->CCMR1 = 0x41; /* set CH1 to capture at every edge */ 
	TIM3->CCER = 0x0B; /* enable CH 1 capture both edges */ 
	TIM3->CR1 = 1; /*
enable TIM3 */
	while (1) {
	while (!(TIM3->SR & 2)) {} /* wait until input edge is captured */
	current = TIM3->CCR1; /* read captured counter value */ 
	period =current - last; /* calculate the period */ 
	last = current;
	frequency = 1000.0f / period;
	last = current;
	}	
}
