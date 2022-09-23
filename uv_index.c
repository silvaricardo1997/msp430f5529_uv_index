#include <msp430.h> 
#include <stdio.h>

#include "adc.h"
#include "ssd1306.h"
#include "delay.h"

volatile float adc_value;
volatile float adc_mVoltage;
volatile int adc_flag = 0;

void timerA0_config(void);

/**
 * main.c
 */
void main(void)
{

    WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
    delay_ms(200);              // Para garantir inicializacao dos perifericos
    ADC_config();

    timerA0_config();
    ssd1306_display_init();
    ssd1306_clear();
	
    ssd1306_print_line(1, "  INICIALIZANDO...");
    delay_ms(200);
    ssd1306_clear();
    
   __enable_interrupt();

	while (1)
	{
	    if (adc_flag == 1)
	    {
	        adc_mVoltage  = (adc_value * 3.3/4096) * 1000 ;

	        if(adc_mVoltage < 225)
	        {
	           ssd1306_print_line(0, "UV: 0 - Baixo");
	           ssd1306_print_line(1, "Voce pode ficar ao ar");
	           ssd1306_print_line(2, "livre com seguranca!");
	        }

	        else if (adc_mVoltage>225 && adc_mVoltage<=325)
	        {
	           ssd1306_print_line(0, "UV: 1 - Baixo");
               ssd1306_print_line(1, "Voce pode ficar ao ar");
               ssd1306_print_line(2, "livre com seguranca!");
	        }

	        else if (adc_mVoltage>325 && adc_mVoltage<=410)
	        {
	           ssd1306_print_line(0, "UV: 2 - Baixo");
               ssd1306_print_line(1, "Voce pode ficar ao ar");
               ssd1306_print_line(2, "livre com seguranca!");
	        }

	        else if (adc_mVoltage>410 && adc_mVoltage<=500)
	        {
	            ssd1306_print_line(0, "UV: 3 - Moderado");
	            ssd1306_print_line(1, "Procure sombra,");
	            ssd1306_print_line(2, "passe protetor ");
	            ssd1306_print_line(3, "solar e use chapeu!" );
	        }

	        else if (adc_mVoltage>500 && adc_mVoltage<=605)
	        {
	           ssd1306_print_line(0, "UV: 4 - Moderado");
	           ssd1306_print_line(1, "Procure sombra,");
	           ssd1306_print_line(2, "passe protetor ");
	           ssd1306_print_line(3, "solar e use chapeu!" );
	        }

	        else if (adc_mVoltage>605 && adc_mVoltage<=695)
	        {
	           ssd1306_print_line(0, "UV: 5 - Moderado");
               ssd1306_print_line(1, "Procure sombra,");
               ssd1306_print_line(2, "passe protetor ");
               ssd1306_print_line(3, "solar e use chapeu!" );
	        }

	        else if (adc_mVoltage>695 && adc_mVoltage<=795)
	        {
	           ssd1306_print_line(0, "UV: 6 - Alto");
               ssd1306_print_line(1, "Procure sombra,");
               ssd1306_print_line(2, "passe protetor ");
               ssd1306_print_line(3, "solar e use chapeu!" );
	        }

	        else if (adc_mVoltage>795 && adc_mVoltage<=880)
	        {
	           ssd1306_print_line(0, "UV: 7 - Alto");
               ssd1306_print_line(1, "Procure sombra,");
               ssd1306_print_line(2, "passe protetor ");
               ssd1306_print_line(3, "solar e use chapeu!");

	        }

	        else if (adc_mVoltage>885 && adc_mVoltage<=975)
	        {
	           ssd1306_print_line(0, "UV: 8 - Muito alto");
               ssd1306_print_line(1, "Evite ficar ao ar");
               ssd1306_print_line(2, "livre. Camisa, protetor");
               ssd1306_print_line(3, "solar e chapeu obrigatorios!");

	        }

	        else if (adc_mVoltage>975 && adc_mVoltage<=1080)
	        {
	           ssd1306_print_line(0, "UV: 9 - Muito alto");
	           ssd1306_print_line(1, "Evite o sol");
	           ssd1306_print_line(2, "Use camisa, protetor");
	           ssd1306_print_line(3, "solar e chapeu!");
	        }

	        else if (adc_mVoltage>1080 && adc_mVoltage<=1170)
	        {
	           ssd1306_print_line(0, "UV: 10 - Muito alto");
               ssd1306_print_line(1, "Evite o sol");
               ssd1306_print_line(2, "Use camisa, protetor");
               ssd1306_print_line(3, "solar e chapeu!");
	        }

	        else if (adc_mVoltage>1170)
	        {
	           ssd1306_print_line(0, "UV: 11+ - Extremo");
               ssd1306_print_line(1, "Evite o sol");
               ssd1306_print_line(2, "Use camisa, protetor");
               ssd1306_print_line(3, "solar, chapeu!");
	        }

	        delay_ms(1000);
	        ssd1306_clear();
	        adc_flag = 0;
	    }
	}

}

//-------------------------------------------------------------------
void timerA0_config(void)
{
    TA0CTL = MC__UP|TASSEL__ACLK;
    TA0CCR0 =  2048 - 1;                        //Frequencia de amostaragem de 32Hz
    TA0CCTL0 = CCIE;

}

//habilita o conversor
#pragma vector = TIMER0_A0_VECTOR
__interrupt void timer0_a0_isr()
{
    //ligando o ADC
    ADC12CTL0 &=~ ADC12SC;
    ADC12CTL0 |= ADC12SC;
}

//-------------------------------------------------------------------
#pragma vector=ADC12_VECTOR
__interrupt void ADC12ISR (void)
{
    adc_value  = ADC12MEM0;

    adc_value += ADC12MEM1;
    adc_value += ADC12MEM2;

    adc_value += ADC12MEM3;
    adc_value += ADC12MEM4;
    adc_value += ADC12MEM5;

    adc_value += ADC12MEM6;
    adc_value += ADC12MEM7;
    adc_value += ADC12MEM8;

    adc_value += ADC12MEM9;
    adc_value += ADC12MEM10;
    adc_value += ADC12MEM11;

    adc_value += ADC12MEM12;
    adc_value += ADC12MEM13;
    adc_value += ADC12MEM14;

    adc_value += ADC12MEM15;
    adc_value = adc_value/16;

    adc_flag = 1;

    __bic_SR_register_on_exit(LPM0_bits);
}
