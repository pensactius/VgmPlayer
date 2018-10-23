#include "Gd3.h"
#include "SdFat.h"

/* This basic test will read the Gd3 data from a vgm file
	in the 'songs' directory. Please, copy the 'songs' 
	directory to the root of your SD card before uploading
	the sketch to your Arduino.
	The song and offset are hardcoded into two constants
	below: songName and offset. If you want to test another
	song you have to update the constants to match both
	file name and the correct gd3 data offset.
*/
#if defined (__AVR_ATmega328P__)    // Arduino UNO, Pro, etc.
#define chipSelect 	10
#elif defined (__AVR_ATmega2560__)  // Arduino Mega 2560
#define chipSelect 	53
#else Unsupported hardware
#endif  

const char *songName { "songs/Defender2" };
const uint32_t offset { 0x139f };

SdFat sd;
File file;
Gd3 gd3;

void setup()
{
	Serial.begin(9600);
	if(!sd.begin(chipSelect,SD_SCK_MHZ(50))) {
    	Serial.print("Init failed!");
    	sd.initErrorHalt();
  	}
	if (!file.open (songName)) {
		Serial.print("Couldn't open file");
		for (;;);
	}

	gd3.begin (&file, offset);
	Serial.println (gd3.getTrack());
	Serial.println (gd3.getGame());	
	Serial.println (gd3.getSystem());
}

void loop()
{

}