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
#ifndef _VGMREADER_H_
#define _VGMREADER_H_

#if defined (__AVR_ATmega328P__)    // Arduino UNO, Pro, etc.
#define BUFSIZE 128  
#elif defined (__AVR_ATmega2560__)  // Arduino Mega 2560
#define BUFSIZE 2048
#else Unsupported hardware
#endif  

#include "Gd3.h"

struct VgmHeader {
  uint8_t id[4];
  uint32_t eofOffset;
  uint32_t vgmVersion;
  uint32_t clkSn7649;
  uint32_t clkYm2413;
  uint32_t gd3Offset;
  uint32_t totalSamples;
  uint32_t loopOffset;
};

class VgmReader
{

public:

            VgmReader (File *fp);
  bool      begin();
  int       read(uint32_t offset, bool srcPCM = false);
  uint8_t   nextByte(bool srcPCM = false);

  // Getters
  uint32_t  getVgmStart ( ) const;
  uint32_t  getFileCursor ( ) const;
  void      getVersion(uint8_t &major, uint8_t &minor) const;
  uint32_t  getDataLength() const;
  char*     getTrack() const;
  char*     getGame() const ;
  char*     getSystem() const;
  void      loop();
  /*  
  void dumpHeader();
    
  void pcmBegin();
  void pcmNewOffset();
  uint32_t getCursor();

  uint8_t getTrackNameLength();
  uint8_t getGameNameLength();
  void attachLCD(LCD *);
*/

private:

  bool parseHeader();
  void parseGD3Info();

  VgmHeader _header;
  File*     _fp;                // SD Card file ptr.
  uint32_t  _vgmDataOffset;     // Offset where vgm data starts
  uint32_t  _dataLength;        // # bytes in vgm data
  uint8_t   _buf[BUFSIZE];      // VGM data buffer
  uint8_t   _pcmBuf[BUFSIZE];   // PCM data buffer
  uint32_t  _pcmStart;          // offset in file where pcm data starts
  uint32_t  _pcmLength;         // # bytes in pcm data

  uint16_t  _bufCursor;         // position in buffer
  uint16_t  _pcmCursor;         // position in pcm buffer
  uint32_t  _pcmNextChunk;      // position in file where next pcm chunk
                                // will be read from.
  uint32_t  _fileCursor;        // position in whole file

  Gd3       _gd3;
  //LCD*      _lcd;
};

#endif
