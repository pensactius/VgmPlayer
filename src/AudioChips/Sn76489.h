/* VGMPlayerSD, a Video Game Music player with Arduino and hardware audio ICs.
   Copyright (C) 2018  Andrés Mata Bretón

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
#ifndef _SN76489_H_
#define _SN76489_H_

#include "Arduino.h"

//==============================================================================
/**
 * \class Sn76489
 * \brief Audio chip SN-76489 class.
 */
class Sn76489
{
public:
   Sn76489(uint8_t wePin);    // Create and init audio chip
   void reset();              // Reset and silence audio chip
   void write(uint8_t data);  // Write data to audio chip

private:
   // Control bus pins.
   uint8_t _wePin;   

#if defined (__AVR_ATmega328P__)              // Arduino UNO, Nano, etc.

  volatile uint8_t& _dataPort = PORTD;        // Data bus in D0-D7
  volatile uint8_t& _dataControl = DDRD;

#elif defined (__AVR_ATmega2560__)            // Arduino Mega 2560  

  volatile uint8_t& _dataPort = PORTA;        // Data bus in PA0-PA7
  volatile uint8_t& _dataControl = DDRA;

#else 
#error Unsopported hardware
#endif     
};

#endif
