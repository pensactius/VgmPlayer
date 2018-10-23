/* Gd3, a Gd3 tag parser from VGM files.
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
#ifndef GD3_H
#define GD3_H

#include "SdFat.h"


class Gd3
{
public:
  // Get Gd3 data from SD card @ given offset
  bool begin(File *fp, uint32_t offset);
  // getters
  inline char *Gd3::getTrack() { return _track; }
  inline char *Gd3::getGame() { return _game; }
  inline char *Gd3::getSystem() { return _system; }
private:
  // Read a wide string from gd3 data and return
  // it as asciiz string.
  void readWString (char *asciiz, bool skip=false);
  File *_fp {nullptr};
  uint32_t _offset {0};
  uint8_t _track[40] {0};
  uint8_t _game[40] {0};
  uint8_t _system[40] {0};
};

#endif