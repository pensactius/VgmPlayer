/*
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
#include "Ym2413.h"


Ym2413::Ym2413(uint8_t csPin, uint8_t wePin, uint8_t AoPin, uint8_t icPin) :
    _csPin(csPin), _wePin(wePin), _aoPin(AoPin), _icPin(icPin) {

  // Data Bus
  _dataControl = 0xFF;          // Data BUS as OUTPUT

  // Control Bus
  pinMode(_csPin, OUTPUT);
  pinMode(_wePin, OUTPUT);
  pinMode(_aoPin, OUTPUT);
  pinMode(_icPin, OUTPUT);

  // Disable chip by default
  digitalWrite(_csPin, 1);
}

void Ym2413::reset() {
  digitalWrite(_icPin, 0);
  delay (100);
  digitalWrite(_icPin, 1);
}

void Ym2413::mute() {

}

void Ym2413::write(uint8_t reg, uint8_t data) {
  // From the datasheet
  // CS WE A0
  // 1  x  x  = Bus inactive
  // 0  0  0  = Select register address
  // 0  0  1  = Write register data
  
  // ------------------------------------------------------
  // Write register address
  // ------------------------------------------------------
  // rise edge, still nothing is sent to UC
  digitalWrite(_csPin, 1);
  digitalWrite(_aoPin, 0);
  _dataPort = reg;
  // fall edge, data is sent to UC
  digitalWrite(_csPin, 0);
  // wait for 12 master clock cycles 
  // (at 3.5Mhz that is 4 microseconds, rounded up)
  delayMicroseconds(4);

  // ------------------------------------------------------
  // Write data
  // ------------------------------------------------------
  // rise edge, still nothing is sent to UC
  digitalWrite(_csPin, 1);
  digitalWrite(_aoPin, 1);
  _dataPort = data;
  // fall edge, data is sent ot UC
  digitalWrite(_csPin, 0);
  // wait for 84 master clock cycles 
  // (at 3.5Mhz is 24 microseconds, rounded up)
  delayMicroseconds(24);

  // Disable UC
  digitalWrite(_csPin, 1);
}