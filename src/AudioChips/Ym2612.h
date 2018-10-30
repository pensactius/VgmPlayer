/**
 * YM2612 test code for AVR.
 * 
 * This program is a simple test code for the YM2612 FM sound chip using an AVR ATmega328p mcu.
 * This program configure the YM2612 to sound like a "grand piano" and play note on / note off in loop.
 * For more informations about wiring please see: http://en.wikipedia.org/wiki/Yamaha_YM2612
 * For more informations about YM2612 registers please see: http://www.smspower.org/maxim/Documents/YM2612
 *
 * @remarks This test code is heavly based on Furrtek's YM2612 test code. Big thanks Furrtek for the help !
 * @warning This test code is made to run on an ATmega328/ATmega168 mcu with a 16MHz external crystal.
 * 
 * @author Fabien Batteix <skywodd@gmail.com>
 * @link http://skyduino.wordpress.com My Blog about electronics
 */
#ifndef YM2612_H
#define YM2612_H
#include <Arduino.h>

//==============================================================================
/**
 * \class Ym2612
 * \brief Audio chip Ym-2612 class.
 */
class Ym2612
{
public:
	// Constructor, assign control pins.	
	Ym2612 (uint8_t icPin, uint8_t csPin, uint8_t wrPin, uint8_t rdPin, uint8_t a0Pin, uint8_t a1Pin);
	
	// Reset and silence audio chip.
	void reset();											

	// Write to port (0/1).
	void write (uint8_t reg, uint8_t data, uint8_t port=0);	

private:
	void _write (uint8_t data);

	// Control bus pins.
	uint8_t	_icPin, _csPin, _wrPin, _rdPin, _a0Pin, _a1Pin;

#if defined (__AVR_ATmega328P__)    // Arduino UNO, Pro, etc.

  uint8_t _dataPort = PORTD;        // Data bus in D0-D7
  uint8_t _dataControl = DDRD;

#elif defined (__AVR_ATmega2560__)  // Arduino Mega 2560  

  uint8_t _dataPort = PORTA;        // Data bus in PA0-PA7
  uint8_t _dataControl = DDRA;

#else 
#error Unsopported hardware
#endif  	
};
/*
// Pinmap (Arduino UNO compatible)
#if (defined ARDUINO_MEGA)
#define YM_IC 			(6) 		// PC5 (= pin A5 for Arduino UNO)
#define YM_CS 			(5) 		// PC4 (= pin A4 for Arduino UNO)
#define YM_WR 			(4) 		// PC3 (= pin A3 for Arduino UNO)
#define YM_RD 			(3) 		// PC2 (= pin A2 for Arduino UNO)
#define YM_A0 			(2) 		// PC1 (= pin A1 for Arduino UNO)
#define YM_A1 			(1) 		// PC0 (= pin A0 for Arduino UNO)
#define YM_CTRL_DDR DDRF
#define YM_CTRL_PORT PORTF
#define YM_DATA_DDR DDRA
#define YM_DATA_PORT PORTA
#endif

const uint8_t YM2612_PINS[] { YM_IC, YM_CS, YM_WR, YM_RD, YM_A0, YM_A1 };

// Private function
void _write_ym(uint8_t data);

void YM2612SetBus();
void YM2612Reset();

//
// Write data into a specific register of the YM2612 channels 1-3
// // @author Andres Mata
// @param reg Destination register address
// @param data Data to write
// 
void YM2612WritePort0(uint8_t reg, uint8_t data);

// 
// Write data into a specific register of the YM2612 channels 4-6
// // @author Andres Mata
// @param reg Destination register address
// @param data Data to write
// 
void YM2612WritePort1(uint8_t reg, uint8_t data);

void YM2612Off();
*/
#endif
