#include "Ym2612.h"

Ym2612 ym2612 (A6, A5, A4, A3, A2, A1);

void setup() {
  ym2612.reset();
   ym2612.write(0x22, 0x08); // LFO off
  ym2612.write(0x27, 0x00); // Note off (channel 0)
  ym2612.write(0x28, 0x00); // Note off (channel 1)
  ym2612.write(0x28, 0x01); // Note off (channel 1)
  ym2612.write(0x28, 0x02); // Note off (channel 2)
  ym2612.write(0x28, 0x03); // Note off (channel 1)
  ym2612.write(0x28, 0x04); // Note off (channel 3)
  ym2612.write(0x28, 0x05); // Note off (channel 4)
  ym2612.write(0x28, 0x06); // Note off (channel 5)
  ym2612.write(0x2B, 0x00); // DAC off

  ym2612.write(0x30, 0x71,0); //
  ym2612.write(0x34, 0x0d,0); //
  ym2612.write(0x38, 0x33,0); //
  ym2612.write(0x3C, 0x01,0); // DT1/MUL
  ym2612.write(0x40, 0x23,0); //
  ym2612.write(0x44, 0x2D,0); //
  ym2612.write(0x48, 0x26,0); //
  ym2612.write(0x4C, 0x00,0); // Total level
  ym2612.write(0x50, 0x5F,0); //
  ym2612.write(0x54, 0x99,0); //
  ym2612.write(0x58, 0x5F,0); //
  ym2612.write(0x5C, 0x94,0); // RS/AR 
  ym2612.write(0x60, 0x05,0); //
  ym2612.write(0x64, 0x05,0); //
  ym2612.write(0x68, 0x05,0); //
  ym2612.write(0x6C, 0x02,0); // AM/D1R
  ym2612.write(0x70, 0x02,0); //
  ym2612.write(0x74, 0x02,0); //
  ym2612.write(0x78, 0x02,0); //
  ym2612.write(0x7C, 0x02,0); // D2R
  ym2612.write(0x80, 0x11,0); //
  ym2612.write(0x84, 0x11,0); //
  ym2612.write(0x88, 0x11,0); //
  ym2612.write(0x8C, 0xb3,0); // D1L/RR

  ym2612.write(0x31, 0x71,0); //
  ym2612.write(0x35, 0x0d,0); //
  ym2612.write(0x39, 0x33,0); //
  ym2612.write(0x3d, 0x01,0); // DT1/MUL
  ym2612.write(0x41, 0x23,0); //
  ym2612.write(0x45, 0x2D,0); //
  ym2612.write(0x49, 0x26,0); //
  ym2612.write(0x4d, 0x00,0); // Total level
  ym2612.write(0x51, 0x5F,0); //
  ym2612.write(0x55, 0x99,0); //
  ym2612.write(0x59, 0x5F,0); //
  ym2612.write(0x5d, 0x94,0); // RS/AR 
  ym2612.write(0x61, 0x05,0); //
  ym2612.write(0x65, 0x05,0); //
  ym2612.write(0x69, 0x05,0); //
  ym2612.write(0x6d, 0x02,0); // AM/D1R
  ym2612.write(0x71, 0x02,0); //
  ym2612.write(0x75, 0x02,0); //
  ym2612.write(0x79, 0x02,0); //
  ym2612.write(0x7d, 0x02,0); // D2R
  ym2612.write(0x81, 0x11,0); //
  ym2612.write(0x85, 0x11,0); //
  ym2612.write(0x89, 0x31,0); //
  ym2612.write(0x8d, 0xb3,0); // D1L/RR
  
  ym2612.write(0x32, 0x71,0); //
  ym2612.write(0x36, 0x0D,0); //
  ym2612.write(0x3a, 0x33,0); //
  ym2612.write(0x3e, 0x01,0); // DT1/MUL
  ym2612.write(0x42, 0x23,0); //
  ym2612.write(0x46, 0x2D,0); //
  ym2612.write(0x4a, 0x26,0); //
  ym2612.write(0x4e, 0x00,0); // Total level
  ym2612.write(0x52, 0x5F,0); //
  ym2612.write(0x56, 0x99,0); //
  ym2612.write(0x5a, 0x5F,0); //
  ym2612.write(0x5e, 0x94,0); // RS/AR 
  ym2612.write(0x62, 0x05,0); //
  ym2612.write(0x66, 0x05,0); //
  ym2612.write(0x6a, 0x05,0); //
  ym2612.write(0x6e, 0x02,0); // AM/D1R
  ym2612.write(0x72, 0x02,0); //
  ym2612.write(0x76, 0x02,0); //
  ym2612.write(0x7a, 0x02,0); //
  ym2612.write(0x7e, 0x02,0); // D2R
  ym2612.write(0x82, 0x11,0); //
  ym2612.write(0x86, 0x11,0); //
  ym2612.write(0x8a, 0x31,0); //
  ym2612.write(0x8e, 0xb4,0); // D1L/RR
  
  ym2612.write(0x90, 0x00,0); //
  ym2612.write(0x94, 0x00,0); //
  ym2612.write(0x98, 0x00,0); //
  ym2612.write(0x9C, 0x00,0); // Proprietary
  ym2612.write(0xB0, 0x03,0); // Feedback/algorithm
  ym2612.write(0xB1, 0x03,0); // Feedback/algorithm
  ym2612.write(0xB2, 0x03,0); // Feedback/algorithm
  ym2612.write(0xB4, 0x93,0); // Both speakers on
  ym2612.write(0xB5, 0x43,0); // Both speakers on
  ym2612.write(0xB6, 0xC4,0); // Both speakers on
  
  ym2612.write(0xA4, 0x22,0); // 
  ym2612.write(0xA0, 0x69,0); // Set frequency ch 1
  
  ym2612.write(0xA5, 0x22,0); // 
  ym2612.write(0xA1, 0xdd,0); // Set frequency ch 2
  
  ym2612.write(0xA6, 0x23,0); // 
  ym2612.write(0xA2, 0x9c,0); // Set frequency ch 3

  ym2612.write(0x30, 0x71,1); //
  ym2612.write(0x34, 0x0d,1); //
  ym2612.write(0x38, 0x33,1); //
  ym2612.write(0x3C, 0x01,1); // DT1/MUL
  ym2612.write(0x40, 0x23,1); //
  ym2612.write(0x44, 0x2D,1); //
  ym2612.write(0x48, 0x26,1); //
  ym2612.write(0x4C, 0x00,1); // Total level
  ym2612.write(0x50, 0x5F,1); //
  ym2612.write(0x54, 0x99,1); //
  ym2612.write(0x58, 0x5F,1); //
  ym2612.write(0x5C, 0x94,1); // RS/AR 
  ym2612.write(0x60, 0x05,1); //
  ym2612.write(0x64, 0x05,1); //
  ym2612.write(0x68, 0x05,1); //
  ym2612.write(0x6C, 0x02,1); // AM/D1R
  ym2612.write(0x70, 0x02,1); //
  ym2612.write(0x74, 0x02,1); //
  ym2612.write(0x78, 0x02,1); //
  ym2612.write(0x7C, 0x02,1); // D2R
  ym2612.write(0x80, 0x11,1); //
  ym2612.write(0x84, 0x11,1); //
  ym2612.write(0x88, 0x11,1); //
  ym2612.write(0x8C, 0xb3,1); // D1L/RR

  ym2612.write(0x31, 0x71,1); //
  ym2612.write(0x35, 0x0d,1); //
  ym2612.write(0x39, 0x33,1); //
  ym2612.write(0x3d, 0x01,1); // DT1/MUL
  ym2612.write(0x41, 0x23,1); //
  ym2612.write(0x45, 0x2D,1); //
  ym2612.write(0x49, 0x26,1); //
  ym2612.write(0x4d, 0x00,1); // Total level
  ym2612.write(0x51, 0x5F,1); //
  ym2612.write(0x55, 0x99,1); //
  ym2612.write(0x59, 0x5F,1); //
  ym2612.write(0x5d, 0x94,1); // RS/AR 
  ym2612.write(0x61, 0x05,1); //
  ym2612.write(0x65, 0x05,1); //
  ym2612.write(0x69, 0x05,1); //
  ym2612.write(0x6d, 0x02,1); // AM/D1R
  ym2612.write(0x71, 0x02,1); //
  ym2612.write(0x75, 0x02,1); //
  ym2612.write(0x79, 0x02,1); //
  ym2612.write(0x7d, 0x02,1); // D2R
  ym2612.write(0x81, 0x11,1); //
  ym2612.write(0x85, 0x11,1); //
  ym2612.write(0x89, 0x31,1); //
  ym2612.write(0x8d, 0xb3,1); // D1L/RR
  
  ym2612.write(0x32, 0x71,1); //
  ym2612.write(0x36, 0x0D,1); //
  ym2612.write(0x3a, 0x33,1); //
  ym2612.write(0x3e, 0x01,1); // DT1/MUL
  ym2612.write(0x42, 0x23,1); //
  ym2612.write(0x46, 0x2D,1); //
  ym2612.write(0x4a, 0x26,1); //
  ym2612.write(0x4e, 0x00,1); // Total level
  ym2612.write(0x52, 0x5F,1); //
  ym2612.write(0x56, 0x99,1); //
  ym2612.write(0x5a, 0x5F,1); //
  ym2612.write(0x5e, 0x94,1); // RS/AR 
  ym2612.write(0x62, 0x05,1); //
  ym2612.write(0x66, 0x05,1); //
  ym2612.write(0x6a, 0x05,1); //
  ym2612.write(0x6e, 0x02,1); // AM/D1R
  ym2612.write(0x72, 0x02,1); //
  ym2612.write(0x76, 0x02,1); //
  ym2612.write(0x7a, 0x02,1); //
  ym2612.write(0x7e, 0x02,1); // D2R
  ym2612.write(0x82, 0x11,1); //
  ym2612.write(0x86, 0x11,1); //
  ym2612.write(0x8a, 0x31,1); //
  ym2612.write(0x8e, 0xb4,1); // D1L/RR
  
  ym2612.write(0x90, 0x00,1); //
  ym2612.write(0x94, 0x00,1); //
  ym2612.write(0x98, 0x00,1); //
  ym2612.write(0x9C, 0x00,1); // Proprietary
  ym2612.write(0xB0, 0x03,1); // Feedback/algorithm
  ym2612.write(0xB1, 0x03,1); // Feedback/algorithm
  ym2612.write(0xB2, 0x03,1); // Feedback/algorithm
  ym2612.write(0xB4, 0x93,1); // Both speakers on
  ym2612.write(0xB5, 0x43,1); // Both speakers on
  ym2612.write(0xB6, 0xC4,1); // Both speakers on
  
  ym2612.write(0xA4, 0x22,1); // 
  ym2612.write(0xA0, 0x39,1); // Set frequency ch 4
  
  ym2612.write(0xA5, 0x22,1); // 
  ym2612.write(0xA1, 0x8d,1); // Set frequency ch 5
  
  ym2612.write(0xA6, 0x23,1); // 
  ym2612.write(0xA2, 0x8c,1); // Set frequency ch 6
}

void loop() {
    delay(2000);
    ym2612.write(0x28, 0xf1); // Key on
    ym2612.write(0x28, 0xf2); // Key on
    ym2612.write(0x28, 0xf3); // Key on
    ym2612.write(0x28, 0xf4); // Key on
    ym2612.write(0x28, 0xf5); // Key on
    ym2612.write(0x28, 0xf6); // Key on
    delay(4000);
    ym2612.write(0x28, 0x01); // Key off
    ym2612.write(0x28, 0x02); // Key off
    ym2612.write(0x28, 0x03); // Key off
    ym2612.write(0x28, 0x04); // Key off
    ym2612.write(0x28, 0x05); // Key off
    ym2612.write(0x28, 0x06); // Key off

}