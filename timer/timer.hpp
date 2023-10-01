/**
 * Arduino library
 *
 * @file    timer.h
 * @brief   Declaration of common timer helper functions
 *
 * @author  Gerardo Detta
 * @date    01/10/2023
 *
 **********************************************************************************************************************/
#ifndef TIMER_H_
#define TIMER_H_

/******************************** MACROS DEFINTION *******************************************************************/


/******************************** FUNCTIONS PROTOTYPES ***************************************************************/


/**
 * @brief Init Arduiono TIM1 to increment tick at 1ms
 * 
 */
void TIMER_init(void);

/**
 * @brief Timer function to check timeouts
 *
 * @param timer_ms starting value of the timer (i.e. "now()")
 * @param delay_ms timeout to check (i.e. "delta")
 * @return true
 * @return false
 */
bool TIMER_isExpired_ms(uint32_t timer_ms, uint32_t delay_ms);

/**
 * @brief Actual time
 *
 * @return uint32_t
 */
uint32_t TIMER_Now_ms(void);

#endif /* TIMER_H_ */

/******************************** END OF FILE ************************************************************************/
