/*
 * adc.c
 *
 *  Created on: 12 de set de 2022
 *      Author: Ricardo Silva Moreira
 */
#include "adc.h"

void ADC_config(void)
{
    // P6.0
    P6SEL = BIT0;                             // Enable A/D channel input (P6.0)
    ADC12CTL0 &=~ ADC12ENC;                   //Zera o bit de ENC

    ADC12CTL0 = ADC12ON   |
                ADC12SHT0_2;                  // Turn on ADC12, set sampling time

    ADC12CTL1 =  ADC12SHS_0 |
                 ADC12SHP   |
                 ADC12SSEL_0|                 // clock de 5MHZ
                 ADC12CONSEQ_1;               // Use sampling timer, A single channel is converted repeatedly

    ADC12MCTL0 = ADC12INCH0;                 // ref+=AVcc, channel = A0

    ADC12MCTL1 = ADC12INCH0;                 // ref+=AVcc, channel = A0
    ADC12MCTL2 = ADC12INCH0;                 // ref+=AVcc, channel = A0

    ADC12MCTL3 = ADC12INCH0;                 // ref+=AVcc, channel = A0
    ADC12MCTL4 = ADC12INCH0;                 // ref+=AVcc, channel = A0
    ADC12MCTL5 = ADC12INCH0;                 // ref+=AVcc, channel = A0

    ADC12MCTL6 = ADC12INCH0;                 // ref+=AVcc, channel = A0
    ADC12MCTL7 = ADC12INCH0;                 // ref+=AVcc, channel = A0
    ADC12MCTL8 = ADC12INCH0;                 // ref+=AVcc, channel = A0

    ADC12MCTL9 = ADC12INCH0;                 // ref+=AVcc, channel = A0
    ADC12MCTL10 = ADC12INCH0;                // ref+=AVcc, channel = A0
    ADC12MCTL11 = ADC12INCH0;                // ref+=AVcc, channel = A0

    ADC12MCTL12 = ADC12INCH0;                // ref+=AVcc, channel = A0
    ADC12MCTL13 = ADC12INCH0;                // ref+=AVcc, channel = A0
    ADC12MCTL14 = ADC12INCH0;                // ref+=AVcc, channel = A0

    ADC12MCTL15 = ADC12INCH0;      // ref+=AVcc, channel = A0, End of Sequence

    ADC12IE = ADC12IFG15;                    // Enable ADC12IFG15
    ADC12CTL0 |= ADC12ENC;                   // Enable conversions
}


