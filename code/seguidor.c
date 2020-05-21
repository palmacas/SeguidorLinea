#include <16F887.h>
#device ADC=8
#fuses INTRC,MCLR,NOWDT,NOPROTECT,NOPUT,NOLVP,NOBROWNOUT,NOCPD
#use delay(clock=8000000)

/* Puertos y registros */
#byte porta = 0x05
#byte portb = 0x06
#byte portc = 0x07
#byte portd = 0x08
#byte porte = 0x09
#define  bt1   pin_b0
#define  bt2   pin_b1
#define  ld1   pin_a4
#define  ld2   pin_e0
#define  ld3   pin_e1
#define  ld4   pin_e2
#define  en1   pin_c2
#define  en2   pin_c1
#define  mot1  pin_d1
#define  mot2  pin_d2
#define  mot3  pin_d0
#define  mot4  pin_c3

/* Variables */
unsigned int sen0,sen1,sen2,sen3,sen4;
unsigned int duty1 = 0;
unsigned int duty2 = 0;
unsigned int um = 90;
int cont = 0;
int meta = 0;

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

void detener(void)
{
   for(;;)
   {
      set_pwm1_duty(0);
      set_pwm2_duty(0);
   }
}

void seguir(void)
{       
   cont = 0;
   leerSensores();
   for(;;)
   {            
      while(sen2 > um)
      {
         duty1 = 128;
         duty2 = 121;
         set_pwm1_duty(duty1);
         set_pwm2_duty(duty2);
         output_high(mot1);
         output_low(mot2);
         output_high(mot3);
         output_low(mot4);
         leerSensores();
         if(sen0 > um && sen4 > um)
         {
            output_high(ld4);
            cont++;
            delay_ms(500);
            if(cont == meta)
            {
               detener();
            }
            output_low(ld4);
         }
      }
      while(sen0 > um)
      {
         duty1 = 80;
         duty2 = 121;
         set_pwm1_duty(duty1);
         set_pwm2_duty(duty2);
         output_high(mot1);
         output_low(mot2);
         output_high(mot3);
         output_low(mot4);
         leerSensores();
         if(sen0 > um && sen4 > um)
         {
            output_high(ld4);
            cont++;
            delay_ms(500);
            if(cont == meta)
            {
               detener();
            }
            output_low(ld4);
         }
      }
      while(sen1 > um)
      {
         duty1 = 90;
         duty2 = 121;
         set_pwm1_duty(duty1);
         set_pwm2_duty(duty2);
         output_high(mot1);
         output_low(mot2);
         output_high(mot3);
         output_low(mot4);         
         leerSensores();
         if(sen0 > um && sen4 > um)
         {
            output_high(ld4);
            cont++;
            delay_ms(500);
            if(cont == meta)
            {
               detener();
            }
            output_low(ld4);
         }
      }
      while(sen3 > um)
      {
         duty1 = 128;
         duty2 = 90;
         set_pwm1_duty(duty1);
         set_pwm2_duty(duty2);
         output_high(mot1);
         output_low(mot2);
         output_high(mot3);
         output_low(mot4);
         delay_ms(20);
         leerSensores();
         if(sen0 > um && sen4 > um)
         {
            output_high(ld4);
            cont++;
            delay_ms(500);
            if(cont == meta)
            {
               detener();
            }
            output_low(ld4);
         }
      }      
      while(sen4 > um)
      {
         duty1 = 128;
         duty2 = 80;
         set_pwm1_duty(duty1);
         set_pwm2_duty(duty2);
         output_high(mot1);
         output_low(mot2);
         output_high(mot3);
         output_low(mot4);
         delay_ms(20);
         leerSensores();
         if(sen0 > um && sen4 > um)
         {
            output_high(ld4);
            cont++;
            delay_ms(500);
            if(cont == meta)
            {
               detener();
            }
            output_low(ld4);
         }
      }
      while(sen0 < um && sen1 < um && sen2 < um && sen3 < um && sen4 < um)
      {
         output_high(ld3);
         duty1 = 128;
         duty2 = 121;         
         set_pwm1_duty(duty1);
         set_pwm2_duty(duty2);
         output_low(mot1);
         output_high(mot2);
         output_low(mot3);
         output_high(mot4);
         leerSensores();
      }
      output_low(ld3);
   }
}

void main()
{
   set_tris_a(0xFF);
   set_tris_b(0xFF);
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
   setup_timer_2(t2_div_by_1,127,1);
   set_pwm1_duty(duty1);
   set_pwm2_duty(duty2);
   
   for(;;)
   {
      output_high(ld1);
      output_high(ld2);
      delay_ms(100);
      if(input(bt1)==1) // Basico
      {
         output_high(ld1);
         output_low(ld2);
         delay_ms(100);
         meta = 2;
         seguir();
      }
      output_low(ld1);
      output_low(ld2);
      delay_ms(100);
      if(input(bt2)==1) // Medio
      {
         output_low(ld1);
         output_high(ld2);         
         delay_ms(100);
         meta = 11;
         seguir();
      }
   }
}
