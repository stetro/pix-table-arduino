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
#ifndef PIX_TABLE_RAINBOW_MODE
	#define PIX_TABLE_RAINBOW_MODE 1
#endif
#ifndef PIX_TABLE_MENU_MODE
	#define PIX_TABLE_MENU_MODE 10
#endif
#ifndef PIX_TABLE_SNAKE_MODE
	#define PIX_TABLE_SNAKE_MODE 2
#endif
#ifndef SNAKE_RIGHT
	#define SNAKE_RIGHT 0
#endif
#ifndef SNAKE_DOWN
	#define SNAKE_DOWN 1
#endif
#ifndef SNAKE_LEFT
	#define SNAKE_LEFT 2
#endif
#ifndef SNAKE_UP
	#define SNAKE_UP 3
#endif

#ifndef STD_ACTIVE_GOF_LEDS
	#define STD_ACTIVE_GOF_LEDS 7+random(10)
#endif
#ifndef STD_COLOR_REFRESH
	#define STD_COLOR_REFRESH 200
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
			menu(),
			rainbow(),
			snake(),
			pushLeft(),
			pushRight(),
			gameOfLife();

	private:
		void
			rainbowLoop(),
			menuLoop(),
			reset(),
			snakeLoop(),
			renderSnake(),
			renderApple(),
			moveSnake(),
			gameOfLifeLoop();
		uint8_t 
			mode,
			field[STD_TABLE_SIZE][STD_TABLE_SIZE],
			gameOfLifeRepeats,
			gameOfLifeActiveColor,
			gameOfLifeSetColor,
			rainbowLoopVar,
			menuPosition,
			leftPushed(),
			rightPushed(),
			snakeDirection,
			snakeList[STD_TABLE_SIZE*STD_TABLE_SIZE][3],
			snakeApple[2],
			left,
			right,
			loopCounter;
		uint32_t 
			Color(byte r, byte g, byte b),
			Wheel(byte WheelPos);
};
