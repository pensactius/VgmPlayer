/*!
 * @file Ym2413.h
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
#ifndef _YM2413_H_
#define _YM2413_H_

#include "Arduino.h"

/**************************************************************************/
/*! 
    @brief  Class for interfacing with YM-2413 hardware audio chip
*/
/**************************************************************************/
class Ym2413
{
public:
  /** Constructor with both ~CS, ~WE and ~Ao pin selection. 
   * Creates the YM-2413 object and initializes the audio chip.
   *
   * \param[in] csPin 
   *    Pin where ~CS is connected.
   * \param[in] wePin 
   *    Pin where ~WE is connected.
   * \param[in] AoPin 
   *    Pin where ~A0 is connected.
   * \param[in] icPin 
   *    Pin where ~IC is connected.
   */
  Ym2413(uint8_t csPin, uint8_t wePin, uint8_t AoPin, uint8_t icPin);

  /** Resets and mutes all voices of the audio chip.
   *
   */
  void reset(); 

  /** Mutes all voices of the audio chip.
   *
   */
  void mute(); 

  /** Writes 'data' value to register 'reg'
   *
   * \param[in] reg
   *    Register address selection
   * \param[in] data 
   *    Data value to write into register
   */
  void write(uint8_t reg, uint8_t data);
  /**************************************************************************/
private:
   // Control bus pins.
  uint8_t _csPin;                             // ~OE pin (Chip Select)
  uint8_t _wePin;                             // ~WE pin (Write)
  uint8_t _aoPin;                             // ~Ao pin (Reg/Data selection)
  uint8_t _icPin;                             // ~IC 

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
