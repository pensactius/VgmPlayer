#include <VgmPlayer.h>

// Pin ~OE del SN-76489
const uint8_t kOePin { A1 };

// Fichero VGM (descomprimido)
const char* const kSongName { "songs/Lemming1" };

// Objeto para el chip de audio SN-76489
Sn76489 psg (kOePin);

// Objeto para el reproductor de archivos VGM
// El reproductor usa 1 chip de audio, y pasamos
// la dirección del chip de audio creado arriba.
VgmPlayer player (1, &psg);

void setup()
{
  // Arduino UNO/Nano usa pin0 y pin1 y por
  // tanto no pueden usar transmisiones serie.
#if not defined (__AVR_ATmega328P__)
  Serial.begin (9600);
#endif  
  
  // Inicialización del reproductor
  player.begin();

  // Intenta leer el fichero VGM
  if (player.read (kSongName)) {

    // Si se ha leído con éxito mostrar información
    // de la canción. Hay que llamar a getVgm() antes
    // porque es el objeto que tiene la información
    // de la canción.
    Serial.println (player.getVgm().getTrack());
    Serial.println (player.getVgm().getGame());
    Serial.println (player.getVgm().getSystem());

    // Reproduce la canción!
    player.play(true);
  }
  else {
    Serial.println ( F("VGM file not found") ); 
  }
}

void loop ()
{

}