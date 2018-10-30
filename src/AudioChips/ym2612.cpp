#include <Arduino.h>
#include "Ym2612.h"

Ym2612::Ym2612 (uint8_t icPin, uint8_t csPin, uint8_t wrPin, uint8_t rdPin, uint8_t a0Pin, uint8_t a1Pin)
  : _icPin(icPin), _csPin(csPin), _wrPin(wrPin), _rdPin(rdPin), _a0Pin(a0Pin), _a1Pin(a1Pin)
{
  // CTRL bus.
  pinMode (_icPin, OUTPUT);
  pinMode (_csPin, OUTPUT);
  pinMode (_wrPin, OUTPUT);
  pinMode (_rdPin, OUTPUT);
  pinMode (_a0Pin, OUTPUT);
  pinMode (_a1Pin, OUTPUT);

  // DATA bus.
  _dataControl = 0xFF;

  // icPin, csPin, WR and RD HIGH by default 
  digitalWrite (_icPin, 1);
  digitalWrite (_csPin, 1);
  digitalWrite (_wrPin, 1);
  digitalWrite (_rdPin, 1);  
  // A0 and A1 LOW by default
  digitalWrite (_a0Pin, 0);
  digitalWrite (_a1Pin, 0);
}

void Ym2612::reset()
{
  digitalWrite (_icPin, 0);
  delayMicroseconds (25);
  digitalWrite (_icPin, 1);
  // Silence channel-0 to channel-6
  for (uint8_t ch=0; ch <=6; ++ch)
    write (0x28, ch);
}

void Ym2612::_write (uint8_t data)
{
  // csPin low
  digitalWrite(_csPin, 0);
  // data to bus
  _dataPort = data;
  // write data
  digitalWrite(_wrPin, 0); 
  delayMicroseconds(1);
  digitalWrite(_wrPin, 1);
  // csPin high
  digitalWrite(_csPin, 1);
  delayMicroseconds(1);

}

void Ym2612::write (uint8_t reg, uint8_t data, uint8_t port=0)
{
  // A1 selects part0 (channels 1-3) or part1 (channels 1-6)
  digitalWrite (_a1Pin, port);
  digitalWrite (_a0Pin, 0);
  // write register selection
  _write (reg);
  // data part 0 (channels 1-3)
  // A1 low, A0 high
  digitalWrite(_a0Pin, 1);
  _write (data);
}

/*
void YM2612SetBus()
{
  //for (auto pin : YM2612_PINS) pinMode (pin, OUTPUT);
  // Pins setup
  YM_CTRL_DDR |= _BV(YM_icPin) | _BV(YM_csPin) | _BV(YM_WR) | _BV(YM_RD) | _BV(YM_A0) | _BV(YM_A1);
  YM_DATA_DDR = 0xFF;

  YM_CTRL_PORT |= _BV(YM_icPin) | _BV(YM_csPin) | _BV(YM_WR) | _BV(YM_RD); // icPin, csPin, WR and RD HIGH by default 
  YM_CTRL_PORT &= ~(_BV(YM_A0) | _BV(YM_A1)); // A0 and A1 LOW by default
}
void YM2612Reset()
{
  // Reset YM-2612 by 0 - 1 icPin
  YM_CTRL_PORT &= ~_BV(YM_icPin);
  delayMicroseconds(25);
  YM_CTRL_PORT |= _BV(YM_icPin);
  //delayMicroseconds(25);
}


void _write_ym(uint8_t data) {
  // csPin LOW
  YM_CTRL_PORT &= ~_BV(YM_csPin); 
  
  // DATA -> YM2612
  //PORTD = (PORTD & 0x03) | (data << 2);           // D2<-N0, D3<-N1 .. D7<-N5
  //PORTB = (PORTB & 0xfc) | ( (data & 0xC0) >> 6); // D11<-N6, D12<-N7
  YM_DATA_PORT = data;

  // Write data
  //_delay_us(1);
  YM_CTRL_PORT &= ~_BV(YM_WR);   
  //_delay_us(1);
  YM_CTRL_PORT |= _BV(YM_WR);

  // csPin HIGH
  YM_CTRL_PORT |= _BV(YM_csPin); 
  _delay_us(1);
  
}

void YM2612WritePort0(uint8_t reg, uint8_t data) {
  YM_CTRL_PORT &= ~_BV(YM_A1); // A1 low |___ Address of FM channel 1-3 
  YM_CTRL_PORT &= ~_BV(YM_A0); // A0 low |
  _write_ym(reg);
  YM_CTRL_PORT &= ~_BV(YM_A1); // A1 low  |___ Data write of FM channel 1-3
  YM_CTRL_PORT |= _BV(YM_A0);  // A0 high |
  _write_ym(data);  
}

void YM2612WritePort1(uint8_t reg, uint8_t data) {
  YM_CTRL_PORT |=  _BV(YM_A1);  // A1 high |___ Address of FM channel 4-6 
  YM_CTRL_PORT &= ~_BV(YM_A0);  // A0 low  |
  _write_ym(reg);
  
  YM_CTRL_PORT |= _BV(YM_A1);   // A1 high |___ Data write of FM channel 4-6
  YM_CTRL_PORT |= _BV(YM_A0);   // A0 high |
  _write_ym(data);  
}

void YM2612Off() {
  YM2612WritePort0(0x28, 0x00); // Key off
  YM2612WritePort0(0x28, 0x01); // Key off
  YM2612WritePort0(0x28, 0x02); // Key off
  YM2612WritePort0(0x28, 0x04); // Key off
  YM2612WritePort0(0x28, 0x05); // Key off
  YM2612WritePort0(0x28, 0x06); // Key off  
}

*/