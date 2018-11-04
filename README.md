# Vgm Player Library

The Vgm Player Library provides a simple library to read Video Game Music (VGM) files from an SD card and play them on real hardware audio chips. 

Chips supported:
- SN-76489
- YM-2612 (_FM only, not fully tested!_)
- YM-2413

The following boards are supported:
- Arduino UNO/Nano 
- Arduino Mega 2560

VGM files can be downloaded from http://vgmrips.net/packs/chip/sn76489. Keep in mind these are compressed files and **MUST** be decompressed before they can be read from the library.  

The library includes a few sample songs in the **songs** directory. They have already been decompressed and can be used directly from the library.
### Conexiones

Conexion SN 76489:
```
clk (14) ...... Arduino D11
~WE ( 5) ...... Arduino D12
Ready(4) ...... N.C
~OE ( 6) ...... Arduino (D10) (Conectar a GND si se necesita este PIN)
D0 - D7  ...... Arduino D9 - D2 (D0 sn76489 <--> D9 Arduino, etc.)
VCC (16) ...... ARduino (+5V)
GND ( 8) ...... Arduino (GND)
```

### Contenido del directorio
```
 sn76489_vgm_player                => Carpeta del proyecto Arduino
  ├── sn76489_vgm_player.ino       => Fichero principal Arduino
  ├── sn76489.h/.cpp               => Funciones de control y escritura al IC sn76489
  ├── VGMPlayer.h/.cpp             => Funciones para reproducir el archivo de música
  ├── vgmdata.h                    => Volcado del archivo VGM en formato de array (vgm_song[])  
  └── Readme.md                    => Este archivo
```
