/**
 * Arduino library
 *
 * @file    timer.c
 * @brief   Implementation of common timer helper functions
 *
 * @author  Gerardo Detta
 * @date    01/10/2023
 *
 **********************************************************************************************************************/

/****************************** SYSTEM INCLUDES **********************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include <limits.h> // for UINT_MAX

#include <avr/io.h>
#include <avr/interrupt.h>

/******************************* DRIVERS INCLUDES ********************************************************************/


/******************************* PROJECT INCLUDES ********************************************************************/
#include "timer.hpp"

/******************************* LOCAL VARIABLES ****************************************************************/

static uint32_t ms_counter = 0;

/******************************* FUNCTIONS ***************************************************************************/



void TIMER_init(void)
{

  // Set Timer 0 in CTC (Clear Timer on Compare Match) mode
  TCCR0A = 0; // Clear Timer0 control register A
  TCCR0B = 0; // Clear Timer0 control register B
  
  // Set the Compare Match Register to generate 1ms interrupt
  /**
   * clk= 16e6 Hz
   * prescaler= 64	-> f=16e6Hz/64=250e3Hz	-> tick ogni 1/250e3Hz=4us
   * Compare ogni 1ms -> 1ms/4us=250
   * 
   * 250-1=249: since starts from 0
   * 
   */
  OCR0A = 249; 
  
  // Enable CTC mode and set prescaler to 64
  TCCR0A |= (1 << WGM01);
  TCCR0B |= (1 << CS01) | (1 << CS00);
  
  // Enable Timer 0 compare match A interrupt
  TIMSK0 |= (1 << OCIE0A);

  // Enable global interrupts
  sei();
}


uint32_t TIMER_Now_ms(void)
{
	return ms_counter;
}


bool TIMER_isExpired_ms(uint32_t timer_ms, uint32_t delay_ms)
{
	const uint32_t count_max = UINT_MAX; /**< Maximum tick count */
	const uint32_t now = ms_counter;	 /**< Current tick count */
	bool is_expired = false;			 /**< true if time is expired */

	if (timer_ms > now)
	{
		const uint32_t delta = count_max - delay_ms;
		if (timer_ms > delta)
		{
			// timer overflows
			if (now >= (timer_ms - delta))
			{
				is_expired = true;
			}
		}
	}
	else
	{
		is_expired = ((now - timer_ms) >= delay_ms) ? true : false;
	}

	return is_expired;
}

ISR(TIMER0_COMPA_vect) {
  // This function will be called every 1ms
  ms_counter++;
}

