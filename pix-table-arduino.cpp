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
	mode = PIX_TABLE_GAMEOFLIFE_MODE;
	
}
void PixTable::begin(){
	strip.begin();
	// Turn LED's off
	strip.show();
	
}
void PixTable::loop(){
	loopCounter++;

	switch(mode){
		case PIX_TABLE_GAMEOFLIFE_MODE:
			gameOfLifeLoop();
			break;
	}
}
void PixTable::gameOfLife(){
	uint8_t x, y;
	
	gameOfLifeRepeats=0;
	gameOfLifeActiveColor=0;
	gameOfLifeSetColor=1;

	for (x=0; x < STD_ACTIVE_GOF_LEDS; x++) {
		field[random(5)][random(5)]=1;
	}
	
}
void PixTable::gameOfLifeLoop(){
	uint8_t x, y;
	
	for (x=0; x < STD_TABLE_SIZE; x++) {
		for (y=0; y < STD_TABLE_SIZE; y++) {
			uint32_t* color = strip.getPixelColor(x,y);
			if(!field[x][y]){
				if(color[0]>0){color[0]=color[0]-1;}
				if(color[1]>0){color[1]=color[1]-1;}
				if(color[2]>0){color[2]=color[2]-1;}
			}
			strip.setPixelColor(x, y, color[0],color[1],color[2]);	
			if(field[x][y] && gameOfLifeSetColor){
				switch(gameOfLifeActiveColor){
					case 0:
						strip.setPixelColor(x, y,220,color[1],color[2]);	
						break;
					case 1:
						strip.setPixelColor(x, y,color[0],220,color[2]);	
						break;
					case 2:
						strip.setPixelColor(x, y,color[0],color[1],220);	
						break;
				}
			}
			
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
	strip.show();
	delay(80);
}

/* Helper functions */
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