/* VgmPlayerSD, a Video Game Music player with Arduino and hardware audio ICs.
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
#ifndef _VgmPlayer_H_
#define _VgmPlayer_H_

#include "AudioChips/Sn76489.h"
#include "AudioChips/Ym2612.h"
#include "VgmReader.h"
#include "SdFat.h"

#if defined (__AVR_ATmega328P__)
#define kChipSelect 10
#elif defined (__AVR_ATmega2560__)
#define kChipSelect 53
#else 
#error Unsupported hardware
#endif

class VgmPlayer
{
public:
  VgmPlayer(uint8_t noChips, Sn76489* sn76489=nullptr, Ym2612* ym2612=nullptr);
  bool begin();
  bool read(const String &fileName);
  void play();
  const VgmReader &getVgm () const { return _vgm; }
  
private:
  void _audioReset();

  uint8_t       _noChips;
  Sn76489*      _sn76489;
  Ym2612*       _ym2612;  
  VgmReader     _vgm;
  uint8_t       _addr, _data;
  unsigned long _currentTime;
  File          _file;
  SdFat         _sd;
};
#endif
