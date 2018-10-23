#include <VgmPlayer.h>

// Pin ~WE del SN-76489
const uint8_t kWePin { A0 };

// Fichero VGM (descomprimido)
const char* const kSongName { "songs/Defender2" };

// Objeto para el chip de audio SN-76489
Sn76489 psg (kWePin);

// Objeto para el reproductor de archivos VGM
// El reproductor usa 1 chip de audio, y pasamos
// la dirección del chip de audio creado arriba.
VgmPlayer player (1, &psg);

void setup()
{
  Serial.begin (9600);
  
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
    player.play();
  }
  else {
    Serial.println ( F("VGM file not found") ); 
  }
}

void loop ()
{

}