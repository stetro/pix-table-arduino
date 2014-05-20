#include "SPI.h"
#include "pix-table-arduino.h"
#include "../Adafruit_WS2801/Adafruit_WS2801.cpp"
#include "modules/Module.h"

Adafruit_WS2801 strip;

GameOfLife gameOfLifeModule =  GameOfLife();
RainBow rainBowModule = RainBow();
Snake snakeModule = Snake();
FlappyBird flappyBirdModule = FlappyBird();
Lander landerModule = Lander();

PixTable::PixTable(){
	Init((uint16_t)STD_TABLE_SIZE, STD_DATA_PIN, STD_CLOCK_PIN);
}

PixTable::~PixTable(void){
}
void PixTable::Init(uint16_t size, uint8_t data, uint8_t clock){
	strip = Adafruit_WS2801((uint16_t)size, (uint16_t)size, data, clock);
	left = 0;
	right = 0;
}
void PixTable::begin(){
	strip.begin();
	strip.show();
}
void PixTable::pushLeft(){
	left = 1;
}
void PixTable::pushRight(){
	right = 1;
}
void PixTable::loop(){
	uint8_t l,r;
	loopCounter++;
	switch(mode){
		case PIX_TABLE_GAMEOFLIFE_MODE:
			gameOfLifeModule.loop(&strip, loopCounter,right,left);
			break;
		case PIX_TABLE_RAINBOW_MODE:
			rainBowModule.loop(&strip, loopCounter, right, left);
			break;
		case PIX_TABLE_SNAKE_MODE:
			snakeModule.loop(&strip, loopCounter, right, left);
			break;
		case PIX_TABLE_FLAPPYBIRD_MODE:
			flappyBirdModule.loop(&strip, loopCounter, right, left);
			break;
		case PIX_TABLE_LANDER_MODE:
			landerModule.loop(&strip, loopCounter, right, left);
			break;
		case PIX_TABLE_MENU_MODE:
			menuLoop();
			break;

	}
	if(mode != PIX_TABLE_MENU_MODE){
		l = leftPushed();
		r = rightPushed();
		if(r && l){
			mode=PIX_TABLE_MENU_MODE;
			menu();
		}
		strip.show();
		delay(50);
	}	
}
void PixTable::menu(){
	menuPosition = 0;
	reset();
}
void PixTable::menuLoop(){
	uint8_t x;
	strip.setPixelColor(PIX_TABLE_GAMEOFLIFE_MODE, STD_TABLE_SIZE-1,gameOfLifeModule.getModuleColor());
	strip.setPixelColor(PIX_TABLE_RAINBOW_MODE,STD_TABLE_SIZE-1,rainBowModule.getModuleColor());
	strip.setPixelColor(PIX_TABLE_SNAKE_MODE,STD_TABLE_SIZE-1,snakeModule.getModuleColor());
	strip.setPixelColor(PIX_TABLE_FLAPPYBIRD_MODE,STD_TABLE_SIZE-1,flappyBirdModule.getModuleColor());
	strip.setPixelColor(PIX_TABLE_LANDER_MODE,STD_TABLE_SIZE-1,landerModule.getModuleColor());

	for (x = 0; x < STD_TABLE_SIZE; ++x){
		strip.setPixelColor(x,STD_TABLE_SIZE-2,0);
	}
	strip.setPixelColor(menuPosition,STD_TABLE_SIZE-2,200,200,200);
	if(rightPushed()){
		menuPosition = (menuPosition + 1) % MODULE_COUNT;
	}
	if(leftPushed()){
		mode = menuPosition;
		switch(menuPosition){
			case PIX_TABLE_GAMEOFLIFE_MODE:
				gameOfLifeModule.initialize(&strip);
				break;
			case PIX_TABLE_RAINBOW_MODE:
				rainBowModule.initialize(&strip);
				break;
			case PIX_TABLE_SNAKE_MODE:
				snakeModule.initialize(&strip);
				break;
			case PIX_TABLE_FLAPPYBIRD_MODE:
				flappyBirdModule.initialize(&strip);
				break;
			case PIX_TABLE_LANDER_MODE:
				landerModule.initialize(&strip);
				break;
		}
		reset();
	}else{
		strip.show();
	}
}
void PixTable::reset(){
	uint8_t x, y;
	for (x=0; x < STD_TABLE_SIZE; x++) {
		for (y=0; y < STD_TABLE_SIZE; y++) {
			strip.setPixelColor(x,y,0);
		}
	}
	strip.show();
}
uint8_t PixTable::rightPushed(){
	if(right){
		right = 0;
		return 1;
	}
	return 0;
}
uint8_t PixTable::leftPushed(){
	if(left){
		left = 0;
		return 1;
	}
	return 0;
}
