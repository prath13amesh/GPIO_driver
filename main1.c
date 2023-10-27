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
	
	GPIO_TYPE mygpio1;
		mygpio1.port = PB;
		mygpio1.pin = 7 ;
		mygpio1.speed = OUT_2MH;
		mygpio1.pinmode = OUT_MODE;
		mygpio1.mode_type = OUT_GP_PP;

	GPIO_TYPE mygpio2;
		mygpio2.port = PB;
		mygpio2.pin = 6 ;
		mygpio2.speed = OUT_2MH;
		mygpio2.pinmode = OUT_MODE;
		mygpio2.mode_type = OUT_GP_PP;

	GPIO_TYPE mygpio3;
		mygpio3.port = PB;
		mygpio3.pin = 5 ;
		mygpio3.speed = OUT_2MH;
		mygpio3.pinmode = OUT_MODE;
		mygpio3.mode_type = OUT_GP_PP;
		
	GPIO_TYPE mygpio4;
		mygpio4.port = PB;
		mygpio4.pin = 4;
		mygpio4.speed = OUT_50MH;
		mygpio4.pinmode = OUT_MODE;
		mygpio4.mode_type = OUT_GP_PP;
	
	
	
	gpio_init(mygpio1);
	gpio_init(mygpio2);
	gpio_init(mygpio3);
	gpio_init(mygpio4);

	

	while(1)
		
	{
		for(int j=4; j<=7; j++){
			gpio_toggle(PB,j);
		for(int i = 0; i<=500000; i++);
		}
		
		for(int j=7; j>=4; j--){
			gpio_toggle(PB,j);
		for(int i = 0; i<=500000; i++);
		}
		/*
		GPIOB->BSRR = (1<<4); //SET PIN4 HIGH
		for(int i = 0; i<=5000000; i++);
		GPIOB->BSRR = 1<<(20); //RESET PIN4 LOW
		for(int i = 0; i<=5000000; i++);
		*/
	
}
	
	
	
}
