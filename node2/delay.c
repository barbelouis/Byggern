/**
 * \file delay.c
 * \brief Delay
 * \author Louis Barbe & Michel Schneider
 * \version 1
 * \date 18 november 2021
 *
 */

/**
 * \fn void delayms(int n)
 * \brief delay in milliseconds
 * \param int n
 */
void delayms(int n)
{
	for (int i = 0; i < n * 6167; i++)
	{

		__asm("nop");
	}
}

/**
 * \fn void delayus(int n)
 * \brief delay in microseconds
 * \param int n
 */
void delayus(int n)
{
	for (int i = 0; i < n * 7; i++)
	{

		__asm("nop");
	}
}