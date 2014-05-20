
class Module {
	public:
		uint32_t getModuleColor();
		void loop(Adafruit_WS2801 * strip, uint8_t loopCounter, uint8_t right, uint8_t left);
		void initialize(Adafruit_WS2801 * strip) ;
};

uint32_t Module::getModuleColor(){};
void Module::loop(Adafruit_WS2801 * strip, uint8_t loopCounter, uint8_t right, uint8_t left){}
void Module::initialize(Adafruit_WS2801 * strip) {};

#include "GameOfLife.cpp"
#include "RainBow.cpp"
#include "Snake.cpp"
#include "FlappyBird.cpp"
#include "Lander.cpp"
