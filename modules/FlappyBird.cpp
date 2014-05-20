class FlappyBird: public Module {
	public:
		FlappyBird();
		~FlappyBird();
		uint32_t getModuleColor();
		void loop(Adafruit_WS2801 * strip, uint8_t loopCounter, uint8_t right, uint8_t left);
		void initialize(Adafruit_WS2801 * strip);
	private:
		uint8_t bird[2];
		uint8_t wall[2];
		void generateNewWall();
		uint8_t negativeModReduction(uint8_t a, uint8_t b);
		void reset(Adafruit_WS2801 * strip);
		uint32_t counter;
		uint8_t ranking;
};



FlappyBird::FlappyBird() {}

FlappyBird::~FlappyBird() {}

void FlappyBird::generateNewWall() {
	wall[0] = 0;
	wall[1] = random(STD_TABLE_SIZE);
}

void FlappyBird::initialize(Adafruit_WS2801 * strip) {
	bird[0] = 2;
	bird[1] = 0xFF;

	wall[0] = 0;
	wall[1] = 2;
	counter = 0;
	ranking = 0;
}

uint32_t FlappyBird::getModuleColor() {
	return 0xFFFF00;
}

void FlappyBird::loop(Adafruit_WS2801 * strip, uint8_t loopCounter, uint8_t right, uint8_t left) {
	uint8_t x, prev;
	if(ranking > 0){
		ranking = ranking + 4;
		if(ranking == 0){
			initialize(strip);
		}
		// draw Ranking
		x = ranking / 4;
		if( x < counter + counter + counter){
			strip->setPixelColor((x/4),0xFFFFFF);
		}
		return;
	}
	for (x = 0; x < STD_TABLE_SIZE; x++) {
		if (x != wall[1]) {
			strip->setPixelColor(x, wall[0], 0xFFFFFF);
		}
		if (wall[0] != 0 ) {
			strip->setPixelColor(x, wall[0] - 1, 0x000000);
		}else if(x != bird[0]){
			strip->setPixelColor(x, negativeModReduction(wall[0], STD_TABLE_SIZE), 0x000000);
		}
	}
	bird[1] = bird[1] + 30;
	if (loopCounter % 4 == 0) {
		if (wall[0] == (STD_TABLE_SIZE-1)) {
			if(bird[0] == wall[1]){
				generateNewWall();
				counter = counter + 1;
			}else{
				reset(strip);
				ranking=4;
				return;
			}
		} else {
			wall[0] = wall[0] + 1;
		}
	}
	if (right) {
		prev = bird[0];
		bird[0] = (bird[0] + 1) % STD_TABLE_SIZE;
	}
	if (left) {
		prev = bird[0];
		bird[0] = negativeModReduction(bird[0], STD_TABLE_SIZE);
	}
	strip->setPixelColor(prev, STD_TABLE_SIZE - 1, 0x000000);
	strip->setPixelColor(bird[0], STD_TABLE_SIZE - 1, 0xFF, bird[1], 0);
}

uint8_t FlappyBird::negativeModReduction(uint8_t a, uint8_t b) {
	if (a == 0) {
		return b - 1;
	} else {
		return (a - 1) % b;
	}

}
void FlappyBird::reset(Adafruit_WS2801 * strip){
	uint8_t x, y;
	for (x=0; x < STD_TABLE_SIZE; x++) {
		for (y=0; y < STD_TABLE_SIZE; y++) {
			strip->setPixelColor(x,y,0);
		}
	}
}


