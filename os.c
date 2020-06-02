#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#define EEPROM_DEF 0xFF

#include <avr/io.h>
#include <util/delay.h>
#include <avr/eeprom.h>

uint8_t eeStep EEMEM = 1;
uint8_t step = 0;
uint8_t stepdelay = 0;
uint8_t firetime = 50;
uint8_t testmode = 0;

void waittime(uint8_t stepdelay);

void waittime(uint8_t stepdelay) {
 for (;stepdelay != 0; stepdelay--) {
  _delay_ms(1);
 }
}

 /* 8 Modes
           PB3 PB4 PB5
     50:   0   0   0
     75:   1   1   0
     100:  1   0   0
     125:  0   1   1
     150:  0   0   1
     175:  0   1   0
     200:  1   0   1
     m:    1   1   1

     C2 = CH01
     C3 = CH02
     C4 = CH03
     C5 = CH04
     D5 = CH05
     D6 = CH06
     D7 = CH07
     D2 = CH08
     B1 = CH09
     B0 = CH10
     D3 = CH11
     D4 = CH12
     B2 = CH13
     C0 = CH14
     C1 = CH15

 */

int main(void) {
 // Ausgaenge / Eingaenge
 DDRB = 0b00000111;
 DDRC = 0b00111111;
 DDRD = 0b11111100;

 // Interne Pull-Ups
 PORTB |= (1<<PB3);
 PORTB |= (1<<PB4);
 PORTB |= (1<<PB5);

 PORTD |= (1<<PD0);
 PORTD |= (1<<PD1);

 step = eeprom_read_byte (&eeStep);

 // 50:   0   0   0
 if ( (!(PINB & ( 1<<PINB3 )) && !(PINB & ( 1<<PINB4 )) && !(PINB & ( 1<<PINB5 )) && testmode == 0) || testmode == 1) {
  step=0;
  eeprom_update_byte(&eeStep, step);
  stepdelay=50-firetime;
 }

 // 75:   1   1   0
 if ( ((PINB & ( 1<<PINB3 )) && (PINB & ( 1<<PINB4 )) && !(PINB & ( 1<<PINB5 )) && testmode == 0) || testmode == 2) {
  step=0;
  eeprom_update_byte(&eeStep, step);
  stepdelay=75-firetime;
 }

 // 100:  1   0   0
 if ( ((PINB & ( 1<<PINB3 )) && !(PINB & ( 1<<PINB4 )) && !(PINB & ( 1<<PINB5 )) && testmode == 0) || testmode == 3) {
  step=0;
  eeprom_update_byte(&eeStep, step);
  stepdelay=100-firetime;
 }

 // 125:  0   1   1
 if ( (!(PINB & ( 1<<PINB3 )) && (PINB & ( 1<<PINB4 )) && (PINB & ( 1<<PINB5 )) && testmode == 0) || testmode == 4) {
  step=0;
  eeprom_update_byte(&eeStep, step);
  stepdelay=125-firetime;
 }

 // 150:  0   0   1
 if ( (!(PINB & ( 1<<PINB3 )) && !(PINB & ( 1<<PINB4 )) && (PINB & ( 1<<PINB5 )) && testmode == 0) || testmode == 5) {
  step=0;
  eeprom_update_byte(&eeStep, step);
  stepdelay=150-firetime;
 }

 // 175:  0   1   0
 if ( (!(PINB & ( 1<<PINB3 )) && (PINB & ( 1<<PINB4 )) && !(PINB & ( 1<<PINB5 )) && testmode == 0) || testmode == 6) {
  step=0;
  eeprom_update_byte(&eeStep, step);
  stepdelay=175-firetime;
 }

 // 200: 1   0   1
 if ( ((PINB & ( 1<<PINB3 )) && !(PINB & ( 1<<PINB4 )) && (PINB & ( 1<<PINB5 )) && testmode == 0) || testmode == 7) {
  step=0;
  eeprom_update_byte(&eeStep, step);
  stepdelay=200-firetime;
 }

 // m:   1   1   1
 if ( ((PINB & ( 1<<PINB3 )) && (PINB & ( 1<<PINB4 )) && (PINB & ( 1<<PINB5 )) && testmode == 0) || testmode == 8) {
  step++;
  eeprom_update_byte(&eeStep, step);

  if(step == 1) {
   PORTC |= (1 << PORTC2);
  }
  if(step == 2) {
   PORTC |= (1 << PORTC3);
  }
  if(step == 3) {
   PORTC |= (1 << PORTC4);
  }
  if(step == 4) {
   PORTC |= (1 << PORTC5);
  }
  if(step == 5) {
   PORTD |= (1 << PORTD5);
  }
  if(step == 6) {
   PORTD |= (1 << PORTD6);
  }
  if(step == 7) {
   PORTD |= (1 << PORTD7);
  }
  if(step == 7) {
	  PORTD |= (1 << PORTD7);
  }
  if(step == 8) {
	  PORTD |= (1 << PORTD2);
  }
  if(step == 9) {
	  PORTB |= (1 << PORTB1);
  }
  if(step == 10) {
	  PORTB |= (1 << PORTB0);
  }
  if(step == 11) {
	  PORTD |= (1 << PORTD3);
  }
  if(step == 12) {
	  PORTD |= (1 << PORTD4);
  }
  if(step == 13) {
	  PORTB |= (1 << PORTB2);
  }
  if(step == 14) {
	  PORTC |= (1 << PORTC0);
  }
  if(step == 15) {
   step=0;
   eeprom_write_byte(&eeStep, step);
   PORTC |= (1 << PORTC1);
  }
  waittime(100);
 }

 while(1) {
  if ( stepdelay == 0 || stepdelay == 25 || stepdelay == 50 || stepdelay == 75 || stepdelay == 100 || stepdelay == 125 || stepdelay == 150) {
   //1
   PORTC |= (1 << PORTC2);
   waittime(firetime);
   PORTC &= ~(1 << PORTC2);
   waittime(stepdelay);

   //2
   PORTC |= (1 << PORTC3);
   waittime(firetime);
   PORTC &= ~(1 << PORTC3);
   waittime(stepdelay);

   //3
   PORTC |= (1 << PORTC4);
   waittime(firetime);
   PORTC &= ~(1 << PORTC4);
   waittime(stepdelay);

   //4
   PORTC |= (1 << PORTC5);
   waittime(firetime);
   PORTC &= ~(1 << PORTC5);
   waittime(stepdelay);

   //5
   PORTD |= (1 << PORTD5);
   waittime(firetime);
   PORTD &= ~(1 << PORTD5);
   waittime(stepdelay);

   //6
   PORTD |= (1 << PORTD6);
   waittime(firetime);
   PORTD &= ~(1 << PORTD6);
   waittime(stepdelay);

   //7
   PORTD |= (1 << PORTD7);
   waittime(firetime);
   PORTD &= ~(1 << PORTD7);
   waittime(stepdelay);

   //8
   PORTD |= (1 << PORTD2);
   waittime(firetime);
   PORTD &= ~(1 << PORTD2);
   waittime(stepdelay);

   //9
   PORTB |= (1 << PORTB1);
   waittime(firetime);
   PORTB &= ~(1 << PORTB1);
   waittime(stepdelay);

   //10
   PORTB |= (1 << PORTB0);
   waittime(firetime);
   PORTB &= ~(1 << PORTB0);
   waittime(stepdelay);

   //11
   PORTD |= (1 << PORTD3);
   waittime(firetime);
   PORTD &= ~(1 << PORTD3);
   waittime(stepdelay);

   //12
   PORTD |= (1 << PORTD4);
   waittime(firetime);
   PORTD &= ~(1 << PORTD4);
   waittime(stepdelay);

   //13
   PORTB |= (1 << PORTB2);
   waittime(firetime);
   PORTB &= ~(1 << PORTB2);
   waittime(stepdelay);

   //14
   PORTC |= (1 << PORTC0);
   waittime(firetime);
   PORTC &= ~(1 << PORTC0);
   waittime(stepdelay);

   //15
   PORTC |= (1 << PORTC1);
   waittime(firetime);
   PORTC &= ~(1 << PORTC1);
   waittime(stepdelay);
  }
  break;
 }
}
