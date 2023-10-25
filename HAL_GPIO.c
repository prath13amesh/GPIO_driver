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