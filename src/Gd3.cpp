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
/*
  gd3.cpp
    This file provides helper functions to parse GD3 info. It's part of 
    the implementation of the VGMReader class.
*/
//#include <SdFat.h>
#include "Gd3.h"

bool Gd3::begin(File *fp, uint32_t offset)
{
  _fp =fp; 
  _offset =offset;

  // First 12 bytes of gd3 data are not relevant to us. 
  _offset += 12; 
  fp->seekSet (_offset);
  // Read track name
  readWString(_track);
  // skip japanese 
  readWString(nullptr, true);
  // Read game name
  readWString(_game);
  // skip japanese
  readWString(nullptr, true);
  readWString(_system);
}
/*
  readWString()
    GD3 info is stored as a 2 byte wide character and terminated with
    two null characters. This helper function reads such strings
    (2 bytes/character) and converts to a C like (1 byte/character) null 
    terminated string.
    Additionally if nullptr is passed as the second parameter it is 
    ignored and the function can be used to just skip the GD3 string 
    and updte the offset to point to the next GD3 string. This can be 
    useful to skip Japanese strings and update the offset to the next 
    English GD3 string.

  Parameters:
    [In] offset: 
      Absolute offset in the VGM file where the GD3 string begins. 
      At the end of the function this offset is updated to point to the 
      next GD3 string so it can be used directly on a successfive 
      call to extract the next GD3 string.

    [Out] strValue:
      Converted C like asciiz string or nullptr if we are not interested
      in the converted string.
*/
void Gd3::readWString (char *asciiz, bool skip)
{
  // c1, c2: two bytes are used to read each 2 byte/char individually
  char c1=0, c2=0, i=0;
  
  /*
    Read each 2-byte wide characters, we are only interested in the first
    one (c1) so we append it to the converted C string (strValue) but only
    if we are not beyond the strValue length, set to 40 in the VGMReader
    class definition.
    We must update the offset by two each time we read a 2-byte char. 
    to ensure we point to the next one.
    We keep reading the GD3 string until we read two consecutives 0x00,0x00.
  */

  do {
    _fp->read(&c1, 1);
    _fp->read(&c2, 1);
    if ( (!skip) && (i < 40) )
    {
      asciiz[i] = c1;
    }
    ++i;
    _offset += 2;
    _fp->seekSet (_offset);
  } while ((c1 != '\0') || (c2 != '\0'));
}
