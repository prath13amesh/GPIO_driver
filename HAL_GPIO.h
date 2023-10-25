#ifndef HAL_GPIO
#define HAL_GPIO

#include "stm32f10x.h"

//STATES
#define LOW		0
#define HIGH	1

//PORT NAMES
#define PA   	GPIOA
#define PB   	GPIOB
#define PC   	GPIOC
#define PD   	GPIOD
#define PE   	GPIOE
#define PF   	GPIOF
#define PG   	GPIOG

//PINMODES
#define OUT_MODE 					((uint32_t) 0x01)
#define IN_MODE 					((uint32_t) 0x02)

//INPUT MODE TYPES
#define IN_ANALOG 				((uint32_t) 0x01) //Analog mode
#define IN_FLOAT					((uint32_t) 0x02) //Floating mode
#define IN_PU_PD					((uint32_t) 0x03) //Input in pull up or pull down

//OUTPUT MODE TYPES
#define OUT_GP_PP 				((uint32_t) 0x01) //General purpose push-pull
#define OUT_GP_OD 				((uint32_t) 0x02) //General purpose open drain
#define OUT_ALT_PP 				((uint32_t) 0x03) //Alternate Function push-pull
#define OUT_ALT_OD				((uint32_t) 0x04) //Alternate Function open drain

//OUTPUT SPEEDS
#define OUT_10MH					((uint32_t) 0x01) //Output at 10MHz
#define OUT_2MH						((uint32_t) 0x02) //Output at 2MHz
#define OUT_50MH					((uint32_t) 0x03) //Output at 50MHz

//CLOCK ENABLE
#define CLOCK_ENABLE_AFIO					(RCC->APB2ENR |= (1<<0)) //Output at 10MHz
#define CLOCK_ENABLE_PA						(RCC->APB2ENR |= (1<<2)) //Output at 10MHz
#define CLOCK_ENABLE_PB						(RCC->APB2ENR |= (1<<3)) //Output at 10MHz
#define CLOCK_ENABLE_PC						(RCC->APB2ENR |= (1<<4)) //Output at 10MHz
#define CLOCK_ENABLE_PD						(RCC->APB2ENR |= (1<<5)) //Output at 10MHz
#define CLOCK_ENABLE_PE						(RCC->APB2ENR |= (1<<6)) //Output at 10MHz

//TO ACCESS CNF PINS USING PINPOS
#define CNF_PINPOS_BIT0				(PINPOS[PINNUMBER]+2)
#define CNF_PINPOS_BIT1				(PINPOS[PINNUMBER]+3)

//configuration stuct
typedef struct
{
	GPIO_TypeDef *port;
	
	uint32_t	pin;
	
	uint32_t	pinmode;
	
	uint32_t	mode_type;
	
	uint32_t	pull;
	
	uint32_t	speed;
	
	uint32_t	alt_func;

}GPIO_TYPE;

//****************************************************//

static void config_pin(GPIO_TypeDef *port, uint32_t PINNUMBER, uint32_t mode_type);

static void config_pin_speed(GPIO_TypeDef *port, uint32_t PINNUMBER, uint32_t	speed, uint32_t pinmode);

//****************************************************//
//									GPIO USER FUNCTIONS
void gpio_write(GPIO_TypeDef *port, uint32_t PINNUMBER, uint32_t state);
void gpio_toggle(GPIO_TypeDef *port, uint32_t PINNUMBER);
void gpio_init(GPIO_TYPE gpio_type);

#endif