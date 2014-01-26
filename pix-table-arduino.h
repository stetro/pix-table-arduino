#if (ARDUINO >= 100)
	#include <Arduino.h>
#else
	#include <WProgram.h>
	#include <pins_arduino.h>
#endif

#ifndef STD_DATA_PIN
	#define STD_DATA_PIN 2
#endif
#ifndef STD_CLOCK_PIN
	#define STD_CLOCK_PIN 3
#endif
#ifndef STD_TABLE_SIZE
	#define STD_TABLE_SIZE 5
#endif
#ifndef PIX_TABLE_GAMEOFLIFE_MODE
	#define PIX_TABLE_GAMEOFLIFE_MODE 0
#endif
#ifndef STD_ACTIVE_GOF_LEDS
	#define STD_ACTIVE_GOF_LEDS 7+random(10)
#endif

class Adafruit_WS2801;

class PixTable{
	public:
		PixTable();
		~PixTable();
		void
			Init(uint16_t size, uint8_t data, uint8_t clock),
			begin(),
			loop(),
			gameOfLife();

	private:
		void
			gameOfLifeLoop();
		uint8_t 
			mode,
			field[STD_TABLE_SIZE][STD_TABLE_SIZE],
			gameOfLifeRepeats,
			gameOfLifeActiveColor,
			gameOfLifeSetColor,
			loopCounter;
		uint32_t 
			Color(byte r, byte g, byte b),
			Wheel(byte WheelPos);
};