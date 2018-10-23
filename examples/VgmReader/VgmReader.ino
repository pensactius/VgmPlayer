#include "VgmReader.h"
#include "SdFat.h"

#if defined (__AVR_ATmega328P__)
#define chipSelect 10
#elif defined (__AVR_ATmega2560__)
#define chipSelect 53
#else 
#error Unsupported hardware
#endif

const char * const songName { "songs/Defender2" };

SdFat sd;
File file;
VgmReader vgm ( &file );

char strMsg[] {0,0,0,0};

void setup()
{
  Serial.begin( 9600 );
  if ( !sd.begin ( chipSelect, SD_SCK_MHZ (50) ) ) {
    Serial.print ( F( "SD init failed!" ) );
    sd.initErrorHalt ( );
  }
  if ( !file.open ( songName ) ) {
    Serial.println ( F( "File open error" ) );
    for (;;);
  }
  if ( vgm.begin() ) {    

    // Print vgm file version
    uint8_t maj, min;
    vgm.getVersion (maj, min);
    Serial.print ( F ( "Version: ") );
    sprintf ( strMsg, "%x.%x", maj, min);
    Serial.println ( strMsg );
    
    // Print track, game and system name
    Serial.println ( vgm.getTrack  ( ) );
    Serial.println ( vgm.getGame   ( ) );
    Serial.println ( vgm.getSystem ( ) );

    // Print where vgm data starts
    uint32_t fileCursor = vgm.getFileCursor ( );
    Serial.print ( F ( "VGM Data Offset: ") );
    Serial.println ( fileCursor, HEX);

    // Read first chunk of vgm data to buffer
    int bytesRead = vgm.read ( fileCursor );
    Serial.print ( F ( "Bytes read: " ) ); Serial.println ( bytesRead );
    if ( bytesRead == -1 ) {
      Serial.println ( F ( "Error reading vgm data" ) );
    }

    // Print first 128 bytes of vgm data
    Serial.println ( F ( "First 128 bytes of VGM data") );
    bytesRead = vgm.read ( fileCursor );
    Serial.print ( F ( "\nBytes read: " ) ); Serial.println ( bytesRead );
    for ( uint8_t i = 0; i != 128; ++i) {
      Serial.print (i % 16 != 0 ? " " : "\n");
      sprintf ( strMsg, "%02X", vgm.nextByte ( ) );
      Serial.print ( strMsg );
    }

    // Print 128 bytes @BUFSIZE - 16
    bytesRead = vgm.read ( vgm.getVgmStart ( ) + BUFSIZE - 16 );
    Serial.print ( F ( "\nBytes read: " ) ); Serial.println ( bytesRead );
    for ( uint8_t i = 0; i != 128; ++i) {
      Serial.print (i % 16 != 0 ? " " : "\n");
      sprintf ( strMsg, "%02X", vgm.nextByte ( ) );
      Serial.print ( strMsg );
    }    
  }
}

void loop()
{

}