#include <16F887.h>
#device ADC=8
#fuses INTRC,NOMCLR,NOWDT,NOPROTECT,NOPUT,NOLVP,NOBROWNOUT,NOCPD
#use delay(clock=8000000)

/* Puertos y registros */
#byte porta = 0x05
#byte portb = 0x06
#byte portc = 0x07
#byte portd = 0x08
#byte porte = 0x09

/* Variables */
int sen0,sen1,sen2,sen3,sen4;

void leerSensores(void)
{
   set_adc_channel(0);
   delay_ms(10);
   sen0 = read_adc();   
   set_adc_channel(1);
   delay_ms(10);
   sen1 = read_adc();
   set_adc_channel(2);
   delay_ms(10);
   sen2 = read_adc();
   set_adc_channel(3);
   delay_ms(10);
   sen3 = read_adc();
   set_adc_channel(4);
   delay_ms(10);
   sen4 = read_adc();
}

void main()
{
   set_tris_a(0x00);
   set_tris_b(0x00);
   set_tris_c(0x00);
   set_tris_d(0x00);
   set_tris_e(0x00);
   porta = 0x00;
   portb = 0x00;
   portc = 0x00;
   portd = 0x00;
   porte = 0x00;
   
   setup_adc(adc_clock_internal);
   setup_adc_ports(san0 | san1 | san2 | san3 | san4 );
   
   setup_ccp1(ccp_pwm);
   setup_ccp2(ccp_pwm);
   setup_timer_2(t2_div_by_4,255,1);
   set_pwm1_duty(127);
   set_pwm2_duty(127);
   
   porta = 0xFF;
   porte = 0x07; 
   
}
