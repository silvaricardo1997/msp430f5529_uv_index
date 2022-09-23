/*
 * delay.c
 *
 *  Created on: 9 de set de 2022
 *      Author: Ricardo Silva Moreira
 *
 */

#include "delay.h"
void delay_us(unsigned int value)
{
    register unsigned int loops =  ((F_CPU * value) >> 2);
    while(loops)
    {
        _delay_cycles(1);
        loops--;
    };
}
void delay_ms(unsigned int value)
{
    while(value)
    {
        delay_us(1000);
        value--;
    };
}


