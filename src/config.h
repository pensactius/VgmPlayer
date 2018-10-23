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

#ifndef _CONFIG_H_
#define _CONFIG_H_

/***********************************************************************
 * Please uncomment the line corresponding to your board, one of:
 *  ARDUINO_UNO
 *  ARDUINO_MEGA
 *  ARDUINO_DUE
 ************************************************************************/
//#define ARDUINO_UNO
#define ARDUINO_MEGA
//#define ARDUINO_DUE

#if (defined ARDUINO_DUE) || (defined ARDUINO_MEGA)
#define LOOP_PIN  43  // Switch button to en/disable vgm loop
#define NEXT_PIN  42  // Push button for next song
#endif

/* Constant for SN-76489 ~WE/~OE.
   Technically there should be two sepparate output pins, one for ~WE and
   another for ~OE. But since they are active/inactive at the same time
   on write operations it's enough with one input and wiring ~WE/~OE
   together.
*/
#define PSG_WE    A0

// Root directory to read songs from
#define VGM_DIR "songs/Sonic The Hedgehog"

#endif

