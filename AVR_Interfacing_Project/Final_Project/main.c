/*
 * main.c
 *
 *  Created on: 14/8/2022
 *      Author: Abdelrahman Gamal
 */

#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>

#define READ_BIT(reg , bit_position)    (reg & (1<<bit_position))
#define SET_BIT(reg , bit_position)     (reg |= (1<<bit_position))
#define TOGGLE_BIT(reg , bit_position)  (reg ^= (1<<bit_position))
#define CLEAR_BIT(reg , bit_position)   (reg &= ~(1<<bit_position))

void _7_Segment_Display(void);
void TIMER0_PWM_Initialization(unsigned char set_duty_cycle_as_percentage);
void TIMER2_Initialization();

volatile unsigned char Seconds_0 = 0;
volatile unsigned char Seconds_1 = 0;
volatile unsigned char Mintes_0 = 0;
volatile unsigned char Mintes_1 = 0;
volatile unsigned char Hours_0 = 0;
volatile unsigned char Hours_1 = 0;

volatile unsigned char PWM_counter = 1;
volatile unsigned char G_Tick = 0;


ISR(INT0_vect)
{
	if(PWM_counter <= 10)
	{
		if(PWM_counter != 10)
		{
			PWM_counter++;
		}
		TIMER0_PWM_Initialization((PWM_counter * 10));

	}


}

ISR(INT1_vect)
{
	_7_Segment_Display();
	TIMER2_Initialization();
	PORTB |= (1 << 0);
	TIMER0_PWM_Initialization(10);
}

ISR(INT2_vect)
{
	if(PWM_counter >= 1)
	{
		if(PWM_counter != 1)
		{
			PWM_counter--;
		}

		TIMER0_PWM_Initialization((PWM_counter * 10));
	}
}

ISR(TIMER2_OVF_vect)
{
	TCNT2 = 5;

	G_Tick++;

	if(4 == G_Tick)
	{
		Seconds_0++;
		if(Seconds_0 == 10)
		{
			Seconds_1++;
			Seconds_0 = 0;
		}
		if(Seconds_1 == 6)
		{
			Mintes_0++;
			Seconds_1 = 0;
		}

		if(Mintes_0 == 10)
		{
			Mintes_1++;
			Mintes_0 = 0;
		}
		if(Mintes_1 == 6)
		{
			Hours_0++;
			Mintes_1 = 0;
		}

		if(Hours_0 == 10)
		{
			Hours_1++;
			Hours_0 = 0;
		}

		if(Hours_1 == 2 && Hours_0 == 4)
		{
			Hours_0 = 0;
			Hours_1 = 0;
		}


		G_Tick = 0;
	}
}



void INT1_Initialization(void)
{
	/* Enable Interrupt of INT1 */
	SET_BIT(GICR , 7);
	/* Fire Interrupt On Rising Edge */
	MCUCR |= (1 << 2) | (1 << 3);
	/* Pin Initialize AS Input */
	CLEAR_BIT(DDRD , 3);
}

void INT0_Initialization(void)
{
	/* Enable Interrupt of INT1 */
	SET_BIT(GICR , 6);
	/* Fire Interrupt On Rising Edge */
	MCUCR |= (1 << 0) | (1 << 1);
	/* Pin Initialize AS Input */
	CLEAR_BIT(DDRD , 2);
}

void INT2_Initialization(void)
{
	/* Enable Interrupt of INT1 */
	SET_BIT(GICR , 5);
	/* Fire Interrupt On Rising Edge */
	MCUCSR |= (1 << 6) ;
	/* Pin Initialize AS Input */
	CLEAR_BIT(DDRB , 2);
}

void Pin_Initialization(void)
{
	/* 7-Segment Initialization */
	DDRC |= (1<<0) | (1<<1) | (1<<2) | (1<<3);
	DDRA = 0x3F; // DDRA = 0b00111111
	/* Pin Initialize  For Switches AS Input*/
	CLEAR_BIT(DDRB , 4);
	CLEAR_BIT(DDRB , 5);
	/* Pin Initialize  For Motor AS Output*/
	DDRB |= (1<<0) | (1<<1) | (1<<3);
}

void TIMER0_PWM_Initialization(unsigned char set_duty_cycle_as_percentage)
{
	/* initialize ORC0 with duty cycle */
	OCR0 = (unsigned char)((set_duty_cycle_as_percentage * 255) / 100);

	/* initialize Timer0 To use in PWM Mode */
	TCCR0 |= (1 << 6) | (1 << 3) | (1 << 5) | (1 << 1);
}


void TIMER2_Initialization()
{
	/*initialize Timer2 With Interrupt */
	TCNT2 = 5;

	TCCR2 |= (1 << 7) | (1 << 0) | (1 << 1) | (1 << 2);

	TIMSK |= (1 << 6);
}




int main(void)
{
	/* Initialization Scope */
	SET_BIT(SREG , 7);
	INT0_Initialization();
	INT1_Initialization();
	INT2_Initialization();
	Pin_Initialization();
	/************************/

	while(1)
	{
		if(READ_BIT(PIND , 3))
		{

			_7_Segment_Display();
			PORTB |= (1 << 0);
			if(READ_BIT(PINB , 5))
			{

				/* Stop Timer */
				CLEAR_BIT(TCCR2 , 1);
				TIMSK &= ~(1 << 6);

				/* Stop Motor */
				CLEAR_BIT(PORTB , 0);
				CLEAR_BIT(PORTB , 1);

				TCCR0 = 0;

				while(READ_BIT(PINB , 5));
			}

			if(READ_BIT(PINB , 4))
			{

				TIMER2_Initialization();
				TIMER0_PWM_Initialization((PWM_counter * 10));
				SET_BIT(PORTB , 0);

				while(READ_BIT(PINB , 4));
			}
		}
		else
		{
			PORTA = 0;
			CLEAR_BIT(PORTB , 0);
			CLEAR_BIT(PORTB , 1);
			Seconds_0 = 0;
			Seconds_1 = 0;
			Mintes_0 = 0;
			Mintes_1 = 0;
			Hours_0 = 0;
			Hours_1 = 0;
		}

	}


}

void _7_Segment_Display(void)
{

	PORTA = (1<<0);
	PORTC = (PORTC & 0xF0) | (Hours_1 & 0x0F);
	_delay_ms(2);

	PORTA = (1<<1);
	PORTC = (PORTC & 0xF0) | (Hours_0 & 0x0F);
	_delay_ms(2);

	PORTA = (1<<2);
	PORTC = (PORTC & 0xF0) | (Mintes_1 & 0x0F);
	_delay_ms(2);

	PORTA = (1<<3);
	PORTC = (PORTC & 0xF0) | (Mintes_0 & 0x0F);
	_delay_ms(2);

	PORTA = (1<<4);
	PORTC = (PORTC & 0xF0) | (Seconds_1 & 0x0F);
	_delay_ms(2);

	PORTA = (1<<5);
	PORTC = (PORTC & 0xF0) | (Seconds_0 & 0x0F);
	_delay_ms(2);
}


