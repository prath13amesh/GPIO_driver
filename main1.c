#include "stm32f10x.h"
#include "HAL_GPIO.h"

int main(void)
{
	/*
//initialize the clock on port B
	RCC->APB2ENR |= (1<<3);
	
//configure Pin4 on portB gpioB
	GPIOB->CRL |= ( (1<<16)  |  (1<<17)  ); //OUTPUT AT 50MHz
	
	GPIOB->CRL &= ~( (unsigned int)(1<<18) | (unsigned int)(1<<19) ); //General Purpose Output
	*/
	
	GPIO_TYPE mygpio;
		mygpio.port = PC;
		mygpio.pin = 13 ;
		mygpio.speed = OUT_50MH;
		mygpio.pinmode = OUT_MODE;
		mygpio.mode_type = OUT_GP_PP; 
	
	gpio_init(mygpio);
	
	
	
	
	
	
	while(1)
		
	{
		
		gpio_toggle(PC,13);
		for(int i = 0; i<=5000000; i++);
		
		/*
		GPIOB->BSRR = (1<<4); //SET PIN4 HIGH
		for(int i = 0; i<=5000000; i++);
		GPIOB->BSRR = 1<<(20); //RESET PIN4 LOW
		for(int i = 0; i<=5000000; i++);
		*/
	}
	
	
}
