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
#include "VgmReader.h"

VgmReader::VgmReader (File *fp) : _fp (fp) {}


//void VgmReader::attachLCD(LCD *lcd) { _lcd = lcd; }

bool VgmReader::begin()
{
  _fp->printName ( &Serial ); Serial.println( );
  if ( !parseHeader ( ) ) return false;
  
  _dataLength = _header.gd3Offset - _vgmDataOffset;
  _fileCursor = _vgmDataOffset;

  _gd3.begin ( _fp, _header.gd3Offset );

  return true;
}

bool VgmReader::parseHeader()
{
  // Read 32 bytes from header
  _fp->read ( &_header, 32 );

  if ( _header.id[0] != 0x56  || //'V' 
       _header.id[1] != 0x67  || //'G'
       _header.id[2] != 0x6D  || //'M'
       _header.id[3] != 0x20 )   //' '
      return false;

  // Store absolute offset of GD3 data
  _header.gd3Offset += 0x14;

  // Read the relative offset to VGM data stream
  _fp->seekSet(0x34);
  uint32_t offset;
  _fp->read (&offset, sizeof(offset));
  _vgmDataOffset = offset != 0 ? ( offset + 0x34 ) : 0x40;

  // Store loop offset relative to vgm song data
  _header.loopOffset += _header.loopOffset != 0 ? ( 0x1C - _vgmDataOffset ) : 0;
    
  return true;
}

int VgmReader::read(uint32_t offset, bool srcPCM = false)
{
  // Set buffer cursor and buffer ptr. to pcm or vgm cursor/buffer.
  uint16_t &bufCursor = srcPCM ? _pcmCursor : _bufCursor;
  uint8_t *buf = srcPCM ? _pcmBuf : _buf;
  // Set file cursor to specified offset
  _fp->seekSet(offset);
  // Read data to pcm or vgm buffer.
  int bytesRead = ( _fp->read ( buf, BUFSIZE ) );
  // Set buffer cursor to first element
  bufCursor = 0;  
  return bytesRead;
}

uint8_t VgmReader::nextByte(bool srcPCM = false)
{
  // srcPCM = false, read from vgm buffer is.
  if (!srcPCM) {
    // If we reached end of buffer read next chunk from SD card.
    if (_bufCursor == BUFSIZE) {
      // TO-DO: Error checking bytes read.
      read (_fileCursor);
    }
    _fileCursor++;

    return _buf[_bufCursor++];
  }

  // srcPCM = true, read from pcm buffer.  
  else {
    // If we reached end of buffer read next chunk from SD card.
    if (_pcmCursor == BUFSIZE) {
      // TO-DO: Error checking bytes read.
      read (_pcmNextChunk, true);
      // TO-DO: Check end of pcm data
      _pcmNextChunk += BUFSIZE;
    }

    return _pcmBuf[_pcmCursor++];
  }  
}

uint32_t VgmReader::getVgmStart ( ) const   { return _vgmDataOffset;  }
uint32_t VgmReader::getFileCursor ( ) const { return _fileCursor;     }
uint32_t VgmReader::getDataLength ( ) const { return _dataLength;     }
char*    VgmReader::getTrack()  const       { return _gd3.getTrack(); }
char*    VgmReader::getGame()   const       { return _gd3.getGame();  }
char*    VgmReader::getSystem() const       { return _gd3.getSystem();}  

void VgmReader::getVersion(uint8_t &major, uint8_t &minor) const
{
  // Version number in BCD-Code. e.g. Version 1.70 is stored as $00 $00 $01 $70  
  minor =   _header.vgmVersion &   0xff;
  major = ( _header.vgmVersion & 0xff00 ) >> 8;
}

void VgmReader::loop()
{  
  read(_header.loopOffset+_vgmDataOffset);
  //Serial.print(F("Loop to "));Serial.println(_header.loopOffset+_vgmDataOffset,HEX);
  _fileCursor = _header.loopOffset+_vgmDataOffset;
}

/*
void VgmReader::pcmBegin()
{   
  // pcmBegin() is called right after cmd 0x67 is
  // found on the VGM stream. 
  // Parse 0x67 0x66 tt ss ss ss ss (data)  
  // Skip 0x66 
  _fp->seekSet(++_fileCursor);         
  uint8_t tt;
  // and read tt value
  _fileCursor += _fp->read (&tt, 1);     
  // only uncompressed pcm data is supported
  if (tt > 0x40) {                      
    Serial.println (F("Unsupported PCM"));
    return;
  }
  else {
    uint32_t pcmOffset {0};                 
    // get pcm length
    _fileCursor += _fp->read (&_pcmLength, 4);
    _pcmStart = _fileCursor;
    // Offset in file for the next pcm data chunk
    _pcmNextChunk = _fileCursor + BUFSIZE;
      
    // I am commenting out reading a pcm chunk now, since usually
    // a 0xE0 cmd will follow a 0x67 to actually set the
    // pcm offset.

    // Cursor in pcm data starts at offset 0
    //_pcmCursor = 0;
    
    // Read BUFSIZE pcm data into pcm buffer
    //readData (_pcmStart, true);    
    // VGM data continues after pcm data section
    _fileCursor += _pcmLength;
    // Read VGM data
    readData (_fileCursor);
  }  
}

void VgmReader::pcmNewOffset()
{
  // Read the new pcm offset
  uint32_t newOffset {0};
  _fp->seekSet (_fileCursor);
  _fileCursor += _fp->read (&newOffset, 4);  
  _bufCursor += 4;
  //Serial.print ("PCM Offset: "); Serial.println (newOffset);
  // Reset pcm cursor to start of buffer
  _pcmCursor = 0;
  // Offset in file for the next pcm data chunk
  _pcmNextChunk = _pcmStart + newOffset + BUFSIZE;  
  //Serial.print ("_pcmNextChunk: "); Serial.println (_pcmNextChunk);  
  // Read BUFSIZE pcm data into pcm buffer
  readData (_pcmStart + newOffset, true);  
}

*/