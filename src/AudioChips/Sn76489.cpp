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

Sn76489::Sn76489(uint8_t oePin, uint8_t wePin) : 
    _wePin (wePin), _oePin (oePin)
{
  _dataControl = 0xFF;          // Data BUS as OUTPUT
  pinMode (_wePin, OUTPUT);     // ~WE OUTPUT
  pinMode (_oePin, OUTPUT);     // ~OE OUTPUT
  digitalWrite (_oePin, HIGH);  // Disable chip by default
}

void Sn76489::reset()
{
  mute();
}

void Sn76489::mute() {
  write (0x9F); // Silence channel 1
  write (0xBF); // Silence channel 2
  write (0xDF); // Silence channel 3
  write (0xFF); // Silence noise channel
}

void Sn76489::write(uint8_t data)
{
  digitalWrite (_oePin, 1);     // ~OE HIGH
  digitalWrite (_wePin, 1);     // ~WE HIGH  

  _dataPort = data;             // Data to BUS

  digitalWrite (_oePin, 0);     // ~OE LOW
  digitalWrite (_wePin, 0);     // ~WE LOW
  delayMicroseconds (14); 

  digitalWrite (_wePin, 1);     // ~WE HIGH
  digitalWrite (_oePin, 1);     // ~OE HIGH
}
