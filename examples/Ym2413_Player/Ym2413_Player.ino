#include <VgmPlayer.h>

// Ym2413 control bus 
const uint8_t kWePin { A0 };
const uint8_t kCsPin { A1 };
const uint8_t kAoPin { A2 };
const uint8_t kIcPin { A3 };

// Fichero VGM (descomprimido)
const char* const kSongName { "songs/04 Turn on The Run" };

// Objeto para el chip de audio YM2413
Ym2413 ym2413_uc (kCsPin, kWePin, kAoPin, kIcPin);

// Objeto para el reproductor de archivos VGM
// El reproductor usa 1 chip de audio, y pasamos
// la dirección del chip de audio creado arriba.
VgmPlayer player (1, nullptr, nullptr, &ym2413_uc);

void setup() {
  // Reset the YM2413 chip, mandatory, otherwise will
  // stay in a reset state all time
  ym2413_uc.reset();
  // Arduino UNO/Nano usa D0 y D1 y por
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

void loop () {

}