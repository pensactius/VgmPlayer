/*
  Sn76489 - Library for Sn76489 chip
  Created by Andres Mata, October 11, 2018.
  Released into the public domain.

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software Foundation,
  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA 
*/
#include "Arduino.h"
#include "Sn76489.h"

Sn76489::Sn76489(uint8_t wePin) : _wePin (wePin) 
{
  DDRA = 0xFF;                  // Data bus is in PA0-PA7
  pinMode (_wePin, OUTPUT);
  digitalWrite (_wePin, HIGH);
}
void Sn76489::reset()
{
  write (0x9F); // Silence channel 1
  write (0xBF); // Silence channel 2
  write (0xDF); // Silence channel 3
  write (0xFF); // Silence noise channel
}
void Sn76489::write(uint8_t data)
{
  digitalWrite (_wePin, 1);   // ~WE HIGH  
  PORTA = data;               // data to bus
  digitalWrite (_wePin, 0);   // ~WE LOW
  delayMicroseconds (14);
  digitalWrite (_wePin, 1);   // ~WE HIGH
}
/*
void SN76489WriteData(char data) {
digitalWrite (PSG_WE, 1); // _WE HIGH

#ifdef ARDUINO_UNO
  // Envia bits 5-0 a PD7-PD2
  PORTD = (PORTD & 0x02) | ( (data & B00111111) << 2 );
  
  // Envia bits 7-6 a PB1-PB0
  PORTB = (PORTB & 0xfc) | ( (data & B11000000) >> 6 );  
#endif
#ifdef ARDUINO_DUE
  // Send data byte to C2-C9 (pin 34 .. pin 41)
  PIOC->PIO_OWER = 0x03FE;
  PIOC->PIO_ODSR = data << 2;
#endif
#ifdef ARDUINO_MEGA
  // Send data byte to PA0-PA7 (pin 22 .. pin 29)
  PORTA = data;
#endif

  // ~WE and ~CE low (active)
  digitalWrite(PSG_WE, 0); 
  delayMicroseconds (14);  
  // ~WE and ~CE high (inactive)
  digitalWrite(PSG_WE, 1);
}

void SN76489SetBus() {
// On all boards A0 is ~WE for SN-76489 and it's an OUTPUT.
  pinMode(PSG_WE, OUTPUT);
  digitalWrite (PSG_WE, HIGH);
}

void SN76489_Off() {
  SN76489WriteData(B10011111);
  SN76489WriteData(B10111111);
  SN76489WriteData(B11011111);
  SN76489WriteData(B11111111);
}
*/