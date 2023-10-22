#include "stm32f10x.h"

int main(void)
{
	
//initialize the clock on port B
	RCC->APB2ENR |= (1<<3);
	
//configure Pin4 on portB gpioB
	GPIOB->CRL |= ( (1<<16)  |  (1<<17)  ); //OUTPUT AT 50MHz
	
	GPIOB->CRL &= ~( (unsigned int)(1<<18) | (unsigned int)(1<<19) ); //General Purpose Output
	
	while(1)
		
	{
		
		GPIOB->BSRR = (1<<4); //SET PIN4 HIGH
		for(int i = 0; i<=5000000; i++);
		GPIOB->BSRR = 1<<(20); //RESET PIN4 LOW
		for(int i = 0; i<=5000000; i++);
	}
}