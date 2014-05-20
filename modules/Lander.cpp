#ifndef COLOR
#define COLOR 0xFFFFFF
#endif
#ifndef CLEAR
#define CLEAR 0x000000
#endif

class Lander: public Module {
	public:
		Lander();
		~Lander();
		uint32_t getModuleColor();
		void loop(Adafruit_WS2801 * strip, uint8_t loopCounter, uint8_t right, uint8_t left);
		void initialize(Adafruit_WS2801 * strip);
};


Lander::Lander() {
}

Lander::~Lander() {
}

void Lander::initialize(Adafruit_WS2801 * strip) {
}

uint32_t Lander::getModuleColor() {
	return 0xFF00FF;
}

void Lander::loop(Adafruit_WS2801 * strip, uint8_t loopCounter, uint8_t right, uint8_t left) {
	uint8_t x;
	loopCounter = loopCounter+loopCounter + loopCounter + loopCounter;
	if(loopCounter < 64){
		for(x=0;x<STD_TABLE_SIZE;x++){
			strip->setPixelColor(0,x,COLOR);
			strip->setPixelColor(STD_TABLE_SIZE-1,x,COLOR);	
			strip->setPixelColor(x,0,COLOR);
			strip->setPixelColor(x,STD_TABLE_SIZE-1,COLOR);	
		}

		strip->setPixelColor(3,1,CLEAR);
		strip->setPixelColor(3,2,CLEAR);
		strip->setPixelColor(3,3,CLEAR);
		strip->setPixelColor(1,1,CLEAR);
		strip->setPixelColor(1,2,CLEAR);
		strip->setPixelColor(1,3,CLEAR);
		strip->setPixelColor(2,1,CLEAR);
		strip->setPixelColor(2,2,CLEAR);
		strip->setPixelColor(2,3,CLEAR);
	}else if(loopCounter < 128){
		for(x=0;x<STD_TABLE_SIZE-1;x++){
			strip->setPixelColor(0,x,CLEAR);
			strip->setPixelColor(STD_TABLE_SIZE-1,x,CLEAR);	
			strip->setPixelColor(x,0,CLEAR);
			strip->setPixelColor(x,STD_TABLE_SIZE-1,CLEAR);	
		}

		strip->setPixelColor(4,4,CLEAR);

		strip->setPixelColor(3,1,COLOR);
		strip->setPixelColor(3,2,COLOR);
		strip->setPixelColor(3,3,COLOR);
		strip->setPixelColor(1,1,COLOR);
		strip->setPixelColor(1,2,COLOR);
		strip->setPixelColor(1,3,COLOR);
		strip->setPixelColor(2,1,COLOR);
		strip->setPixelColor(2,2,CLEAR);
		strip->setPixelColor(2,3,COLOR);

	}else if(loopCounter < 192){
		for(x=0;x<STD_TABLE_SIZE-1;x++){
			strip->setPixelColor(0,x,CLEAR);
			strip->setPixelColor(STD_TABLE_SIZE-1,x,CLEAR);	
			strip->setPixelColor(x,0,CLEAR);
			strip->setPixelColor(x,STD_TABLE_SIZE-1,CLEAR);	
		}

		strip->setPixelColor(3,1,CLEAR);
		strip->setPixelColor(3,2,CLEAR);
		strip->setPixelColor(3,3,CLEAR);
		strip->setPixelColor(1,1,CLEAR);
		strip->setPixelColor(1,2,CLEAR);
		strip->setPixelColor(1,3,CLEAR);
		strip->setPixelColor(2,1,CLEAR);
		strip->setPixelColor(2,2,COLOR);
		strip->setPixelColor(2,3,CLEAR);
	}else{
		strip->setPixelColor(2,2,CLEAR);
	}	
}
