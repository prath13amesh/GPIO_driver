#include "HAL_GPIO.h"
#include <stdint.h>





/**********EVERY PORT IN THE CONTROL HIGH AND LOW REGISTER HAS ASSOCIATED PINS WITH IT*****/
/**********EVERY PORT HAS 4 PINS PERFORMING VARIOUS OPERATIONS******************/
/*BELOW GIVEN IS THE ARRAY INDICATING ADDRESSES OF THE LOCATION OF START OF EACH PORT*/

uint32_t PINPOS[16] =
{
	(0x00),		//PIN0 STARTS AT POSITION 0					//GPIOx_CRL
	(0x04),		//PIN1 STARTS AT POSITION 4
	(0x08),
	(0x0C),
	(0X10),
	(0X14),
	(0X18),
	(0X1C),		//PIN7 STARTS AT POSITION 28
	(0x00),		//PIN8 STARTS AT POSITION 0					//GPIOx_CRH
	(0x04),		//PIN9 STARTS AT POSITON 4
	(0x08),
	(0x0C),
	(0X10),
	(0X14),
	(0X18),
	(0X1C)		//PIN16 STARTS AT POSITION 28
	
};
//**************************************************************************888
static void config_pin(GPIO_TypeDef *port, uint32_t PINNUMBER, uint32_t mode_type)
{
	if(PINNUMBER>8)		//CHR
	{
		switch(mode_type)
		{
			case OUT_GP_PP | IN_ANALOG:
				port->CRH &= ~(		(1<<CNF_PINPOS_BIT0)		|		(1<<CNF_PINPOS_BIT1)		);
			break;
			
			case OUT_GP_OD	|	IN_FLOAT:
				port->CRH |= (1<<CNF_PINPOS_BIT0);
				port->CRH &=	(1<<CNF_PINPOS_BIT1);
			break;
			
			case OUT_ALT_PP	|	 IN_PU_PD:
					port->CRH	|=	OUT_ALT_PP<<(CNF_PINPOS_BIT0);
			break;
			
			case OUT_ALT_OD:
				port->CRH	|=	 OUT_ALT_OD<<(CNF_PINPOS_BIT0);
			break;
		}//end switch case
	}
	else							//CLR
	{
		switch(mode_type)
		{
			case OUT_GP_PP | IN_ANALOG:
				port->CRL &= ~(		(1<<CNF_PINPOS_BIT0)		|		(1<<CNF_PINPOS_BIT1)		);
			break;
			
			case OUT_GP_OD	|	IN_FLOAT:
				port->CRL |= (1<<CNF_PINPOS_BIT0);
				port->CRL &=	(1<<CNF_PINPOS_BIT1);
			break;
			
			case OUT_ALT_PP	|	 IN_PU_PD:
					port->CRL	|=	OUT_ALT_PP<<(CNF_PINPOS_BIT0);
			break;
			
			case OUT_ALT_OD:
				port->CRL	|=	 OUT_ALT_OD<<(CNF_PINPOS_BIT0);
			break;
		}//end switch case
	}
}
//**********************************************************************************
static void config_pin_speed(GPIO_TypeDef *port, uint32_t PINNUMBER, uint32_t	speed, uint32_t pinmode)
{
	if(PINNUMBER>8)
	{
		if(pinmode == IN_MODE)		//SET CRH TO INPUT MODE
		{
			port->CRH 	&= 		~(1<<(PINPOS[PINNUMBER])	|		(1<<(PINPOS[PINNUMBER]+1)));
		}
		else{
			port->CRH 	|=		(speed<<(PINPOS[PINNUMBER]));
			}
		}
	else
	{
		if(pinmode == IN_MODE)		//SET CRL TO INPUT MODE
		{
			port->CRL 	&= 		~(1<<(PINPOS[PINNUMBER])	|		(1<<(PINPOS[PINNUMBER]+1)));
		}
		else{
			port->CRL 	|=		(speed<<(PINPOS[PINNUMBER]));
			}
	}
		
}
//**********************************************************************************
void gpio_write(GPIO_TypeDef *port, uint32_t PINNUMBER, uint32_t state)
	{
		if(state)
		{
			port->BSRR = (1<<PINNUMBER);
		}
		else{
			port->BSRR = (1<< (PINNUMBER+16));
		}
	}
	//********************************************************************************
	void gpio_toggle(GPIO_TypeDef *port, uint32_t PINNUMBER)
	{
		port->ODR	^=(1<<PINNUMBER);
	}
	
	void gpio_init(GPIO_TYPE gpio_type)
	{
		if(gpio_type.port== PA)
			CLOCK_ENABLE_PA;
		if(gpio_type.port== PB)
			CLOCK_ENABLE_PB;
		if(gpio_type.port== PC)
			CLOCK_ENABLE_PC;
		if(gpio_type.port== PD)
			CLOCK_ENABLE_PD;
		if(gpio_type.port== PE)
			CLOCK_ENABLE_PE;
		
		config_pin(gpio_type.port, gpio_type.pin, gpio_type.mode_type);
		config_pin_speed(gpio_type.port, gpio_type.pin, gpio_type.speed, gpio_type.pinmode);
	}
	//**********************************************************************************
	void config_gpio_interrupt(GPIO_TypeDef *port, uint32_t PINNUMBER, edge_select edge)
	{
		RCC->APB2ENR = (1<<0);							//ENABLING AFIO TO SET PIN FOR INTERRUPT
		if(port == PA)
		{
			switch(PINNUMBER)
			{
				case 0:
					AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI0_PA;
				break;
				case 1:
					AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI1_PA;
				break;
				case 2:
					AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI2_PA;
				break;
				case 3:
					AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI3_PA;
				break;
				case 4:
					AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI4_PA;
				break;
				case 5:
					AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI5_PA;
				break;
				case 6:
					AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI6_PA;
				break;
				case 7:
					AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI7_PA;
				break;
				case 8:
					AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI8_PA;
				break;
				case 9:
					AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI9_PA;
				break;
				case 10:
					AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI10_PA;
				break;
				case 11:
					AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI11_PA;
				break;
				case 12:
					AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI12_PA;
				break;
				case 13:
					AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI13_PA;
				break;
				case 14:
					AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI14_PA;
				break;
				case 15:
					AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI15_PA;
				break;
				
			}
		}//END FOR PORT A INTERRUPTS
		
		if(port == PB)
		{
			switch(PINNUMBER)
			{
				case 0:
					AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI0_PB;
				break;
				case 1:
					AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI1_PB;
				break;
				case 2:
					AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI2_PB;
				break;
				case 3:
					AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI3_PB;
				break;
				case 4:
					AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI4_PB;
				break;
				case 5:
					AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI5_PB;
				break;
				case 6:
					AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI6_PB;
				break;
				case 7:
					AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI7_PB;
				break;
				case 8:
					AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI8_PB;
				break;
				case 9:
					AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI9_PB;
				break;
				case 10:
					AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI10_PB;
				break;
				case 11:
					AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI11_PB;
				break;
				case 12:
					AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI12_PB;
				break;
				case 13:
					AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI13_PB;
				break;
				case 14:
					AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI14_PB;
				break;
				case 15:
					AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI15_PB;
				break;
				
			}
		}//END FOR PORT B INTERRUPTS
		
		if(port == PC)
		{
			switch(PINNUMBER)
			{
				case 0:
					AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI0_PC;
				break;
				case 1:
					AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI1_PC;
				break;
				case 2:
					AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI2_PC;
				break;
				case 3:
					AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI3_PC;
				break;
				case 4:
					AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI4_PC;
				break;
				case 5:
					AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI5_PC;
				break;
				case 6:
					AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI6_PC;
				break;
				case 7:
					AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI7_PC;
				break;
				case 8:
					AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI8_PC;
				break;
				case 9:
					AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI9_PC;
				break;
				case 10:
					AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI10_PC;
				break;
				case 11:
					AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI11_PC;
				break;
				case 12:
					AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI12_PC;
				break;
				case 13:
					AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI13_PC;
				break;
				case 14:
					AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI14_PC;
				break;
				case 15:
					AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI15_PC;
				break;
				
			}
		}//END FOR PORT C INTERRUPTS
		
		if(port == PD)
		{
			switch(PINNUMBER)
			{
				case 0:
					AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI0_PD;
				break;
				case 1:
					AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI1_PD;
				break;
				case 2:
					AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI2_PD;
				break;
				case 3:
					AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI3_PD;
				break;
				case 4:
					AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI4_PD;
				break;
				case 5:
					AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI5_PD;
				break;
				case 6:
					AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI6_PD;
				break;
				case 7:
					AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI7_PD;
				break;
				case 8:
					AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI8_PD;
				break;
				case 9:
					AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI9_PD;
				break;
				case 10:
					AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI10_PD;
				break;
				case 11:
					AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI11_PD;
				break;
				case 12:
					AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI12_PD;
				break;
				case 13:
					AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI13_PD;
				break;
				case 14:
					AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI14_PD;
				break;
				case 15:
					AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI15_PD;
				break;
				
			}
		}//END FOR PORT D INTERRUPTS
		
		if(port == PE)
		{
			switch(PINNUMBER)
			{
				case 0:
					AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI0_PE;
				break;
				case 1:
					AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI1_PE;
				break;
				case 2:
					AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI2_PE;
				break;
				case 3:
					AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI3_PE;
				break;
				case 4:
					AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI4_PE;
				break;
				case 5:
					AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI5_PE;
				break;
				case 6:
					AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI6_PE;
				break;
				case 7:
					AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI7_PE;
				break;
				case 8:
					AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI8_PE;
				break;
				case 9:
					AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI9_PE;
				break;
				case 10:
					AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI10_PE;
				break;
				case 11:
					AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI11_PE;
				break;
				case 12:
					AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI12_PE;
				break;
				case 13:
					AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI13_PE;
				break;
				case 14:
					AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI14_PE;
				break;
				case 15:
					AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI15_PE;
				break;
				
			}
		}//END FOR PORT E INTERRUPTS
		
		if(port == PF)
		{
			switch(PINNUMBER)
			{
				case 0:
					AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI0_PF;
				break;
				case 1:
					AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI1_PF;
				break;
				case 2:
					AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI2_PF;
				break;
				case 3:
					AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI3_PF;
				break;
				case 4:
					AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI4_PF;
				break;
				case 5:
					AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI5_PF;
				break;
				case 6:
					AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI6_PF;
				break;
				case 7:
					AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI7_PF;
				break;
				case 8:
					AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI8_PF;
				break;
				case 9:
					AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI9_PF;
				break;
				case 10:
					AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI10_PF;
				break;
				case 11:
					AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI11_PF;
				break;
				case 12:
					AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI12_PF;
				break;
				case 13:
					AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI13_PF;
				break;
				case 14:
					AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI14_PF;
				break;
				case 15:
					AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI15_PF;
				break;
				
			}
		}//END FOR PORT F INTERRUPTS
		
		if(port == PG)
		{
			switch(PINNUMBER)
			{
				case 0:
					AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI0_PG;
				break;
				case 1:
					AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI1_PG;
				break;
				case 2:
					AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI2_PG;
				break;
				case 3:
					AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI3_PG;
				break;
				case 4:
					AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI4_PG;
				break;
				case 5:
					AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI5_PG;
				break;
				case 6:
					AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI6_PG;
				break;
				case 7:
					AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI7_PG;
				break;
				case 8:
					AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI8_PG;
				break;
				case 9:
					AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI9_PG;
				break;
				case 10:
					AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI10_PG;
				break;
				case 11:
					AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI11_PG;
				break;
				case 12:
					AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI12_PG;
				break;
				case 13:
					AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI13_PG;
				break;
				case 14:
					AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI14_PG;
				break;
				case 15:
					AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI15_PG;
				break;
				
			}
		}//END FOR PORT G INTERRUPTS
//****************************************************************
//					DETERMINING THE EDGE ON WHICH THE INTERRUPT WILL ACT		
		if (edge == RISING_EDGE)
		{
			EXTI->RTSR |= (1<<PINNUMBER);
		}
		else if (edge == FALLING_EDGE)
		{
			EXTI->FTSR |= (1<<PINNUMBER);
		}
		else if (edge == RISING_FALLING_EDGE)
		{
			EXTI->RTSR |= (1<<PINNUMBER);
			EXTI->FTSR |= (1<<PINNUMBER);
		}
	}
//*****************************************************************
//				TO ENABLE THE ASSINGED INTRRUPT PINS ON THE BOARD
void enable_gpio_interrupt(uint32_t PINNUMBER, IRQn_Type irqNumber)
	{
		//ENABLING INTERRUPT IN EXTI
		EXTI->IMR |= 1<<PINNUMBER;
		//ENABLING INTERRUPT IN NVIC
		NVIC_EnableIRQ(irqNumber);
	}
//****************************************************************
//			FOR CLEARING ASSIGNED INTERRUPT PIN
void clear_gpio_interrupt(uint32_t PINNUMBER)
	{
		EXTI->PR |= (1<<PINNUMBER);

	}	
	