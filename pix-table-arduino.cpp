#include "SPI.h"
#include "pix-table-arduino.h"
#include "../Adafruit_WS2801/Adafruit_WS2801.cpp"

Adafruit_WS2801 strip;

PixTable::PixTable(){
	Init((uint16_t)STD_TABLE_SIZE, STD_DATA_PIN, STD_CLOCK_PIN);
}

PixTable::~PixTable(void){
	if(field != NULL){
		free(field);
	}
}
void PixTable::Init(uint16_t size, uint8_t data, uint8_t clock){
	strip = Adafruit_WS2801((uint16_t)size, (uint16_t)size, data, clock);
	left = 0;
	right = 0;
	mode = PIX_TABLE_GAMEOFLIFE_MODE;
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
	loopCounter++;
	switch(mode){
		case PIX_TABLE_GAMEOFLIFE_MODE:
			gameOfLifeLoop();
			break;
		case PIX_TABLE_RAINBOW_MODE:
			rainbowLoop();
			break;
		case PIX_TABLE_SNAKE_MODE:
			snakeLoop();
			break;
		case PIX_TABLE_MENU_MODE:
			menuLoop();
			break;
	}
}
void PixTable::menu(){
	mode = PIX_TABLE_MENU_MODE;
	menuPosition = 0;
	reset();
}
void PixTable::menuLoop(){
	uint8_t x;
	strip.setPixelColor(PIX_TABLE_GAMEOFLIFE_MODE,STD_TABLE_SIZE-1,200,0,200);
	strip.setPixelColor(PIX_TABLE_RAINBOW_MODE,STD_TABLE_SIZE-1,0,200,200);
	strip.setPixelColor(PIX_TABLE_SNAKE_MODE,STD_TABLE_SIZE-1,0,200,0);
	for (x = 0; x < STD_TABLE_SIZE; ++x){
		strip.setPixelColor(x,STD_TABLE_SIZE-2,0);
	}
	strip.setPixelColor(menuPosition,STD_TABLE_SIZE-2,200,200,200);
	if(rightPushed()){
		menuPosition = (menuPosition + 1) % 3;
	}
	if(leftPushed()){
		mode = menuPosition;
		reset();
	}else{
		strip.show();
	}
}
void PixTable::snake(){
	mode = PIX_TABLE_SNAKE_MODE;
	reset();
}
void PixTable::snakeLoop(){
	uint8_t r,l;




	r = rightPushed();
	l = leftPushed();
	if(r&&l){
		menu();
	}else{
		strip.show();
	}
}
void PixTable::rainbow(){
	mode = PIX_TABLE_RAINBOW_MODE;
	rainbowLoopVar =0;
	reset();
}
void PixTable::rainbowLoop(){
	uint8_t i, j, r, l;
	rainbowLoopVar++;
	for (i=0; i < strip.numPixels(); i++) {
		strip.setPixelColor(i, Wheel( ((i * 256 / strip.numPixels()) + rainbowLoopVar) % 256) );
	}
	l=leftPushed();
	r=rightPushed();
	if(r && l){
		menu();
	}else{
		strip.show();
	}
	delay(50);
}
void PixTable::gameOfLife(){
	uint8_t x, y;
	mode = PIX_TABLE_GAMEOFLIFE_MODE;
	gameOfLifeRepeats=0;
	gameOfLifeActiveColor=0;
	gameOfLifeSetColor=1;
	for (x=0; x < STD_ACTIVE_GOF_LEDS; x++) {
		field[random(5)][random(5)]=1;
	}
	reset();
}
void PixTable::gameOfLifeLoop(){
	uint8_t x, y, r, l;
	for (x=0; x < STD_TABLE_SIZE; x++) {
		for (y=0; y < STD_TABLE_SIZE; y++) {
			uint32_t* color = strip.getPixelColor(x,y);
			if(!field[x][y]){
				if(color[0]>0){color[0]=color[0]-1;}
				if(color[1]>0){color[1]=color[1]-1;}
				if(color[2]>0){color[2]=color[2]-1;}
			}else{
				if(color[gameOfLifeActiveColor]!= STD_COLOR_REFRESH){
					color[gameOfLifeActiveColor]+=2;
				}
			}

			strip.setPixelColor(x, y, color[0],color[1],color[2]);	
		}
	}
	gameOfLifeSetColor = 0;
	if(loopCounter % 64 == 0){
		gameOfLifeRepeats++;
		gameOfLifeSetColor = 1;
		for (x=0; x < STD_TABLE_SIZE; x++) {
			for (y=0; y < STD_TABLE_SIZE; y++) {
				field[x][y]=0;
			}
		}
		for (x=0; x < STD_ACTIVE_GOF_LEDS; x++) {
			field[random(5)][random(5)]=1;
		}
	}
	if(gameOfLifeRepeats == 4){
		gameOfLifeRepeats = 0;
		gameOfLifeActiveColor = (gameOfLifeActiveColor+1)%3;
	}
	l=leftPushed();
	r=rightPushed();
	if(r && l){
		menu();
	}
	strip.show();
	delay(50);
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
/* Helper functions by Adafruit */
uint32_t PixTable::Color(byte r, byte g, byte b)
{
	uint32_t c;
	c = r;
	c <<= 8;
	c |= g;
	c <<= 8;
	c |= b;
	return c;
}
uint32_t PixTable::Wheel(byte WheelPos)
{
	if (WheelPos < 85) {
		return Color(WheelPos * 3, 255 - WheelPos * 3, 0);
	} else if (WheelPos < 170) {
		WheelPos -= 85;
		return Color(255 - WheelPos * 3, 0, WheelPos * 3);
	} else {
		WheelPos -= 170;
		return Color(0, WheelPos * 3, 255 - WheelPos * 3);
	}
}
