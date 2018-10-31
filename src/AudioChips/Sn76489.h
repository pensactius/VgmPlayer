/*!
 * @file Sn76489.h
 *
 * This is part of the Vgm Player Library for the Arduino platform. 
 *
 * Written by Andrés Mata for PensActius
 * 
 * Copyright (C) 2018  Andrés Mata Bretón
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA 
 */
#ifndef _SN76489_H_
#define _SN76489_H_

#include "Arduino.h"

/**************************************************************************/
/*! 
    @brief  Class for interfacing with SN-76489 hardware audio chip
*/
/**************************************************************************/
class Sn76489
{
public:
  /** Constructor with ~WE pin selection.
   *  Creates the SN-76489 object and initializes the audio chip.
   *
   * \param[in] wePin 
   *    Pin where ~WE is connected.
   */
  Sn76489(uint8_t wePin);
  /** Reset and silence all voices of the audio chip.
   *
   */
  void reset(); 
  /** Writes a data byte to the audio chip.
   *
   * \param[in] data 
   *    Byte value to send to the audio chip.
   */
  /**************************************************************************/
  void write(uint8_t data);

private:
   // Control bus pins.
   uint8_t _wePin;                            // ~WE pin

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
