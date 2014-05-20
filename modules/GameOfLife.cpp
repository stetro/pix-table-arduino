class GameOfLife: public Module {
	public:
		GameOfLife();
		~GameOfLife();
		uint32_t getModuleColor();
		void loop(Adafruit_WS2801 * strip, uint8_t loopCounter, uint8_t right, uint8_t left);
		void initialize(Adafruit_WS2801 * strip);
	private:
		uint8_t gameOfLifeRepeats;
		uint8_t gameOfLifeActiveColor;
		uint8_t gameOfLifeSetColor;
		uint8_t field[STD_TABLE_SIZE][STD_TABLE_SIZE];
};



GameOfLife::GameOfLife() {
	gameOfLifeRepeats = 0;
	gameOfLifeActiveColor = 0;
	gameOfLifeSetColor = 0;
}

GameOfLife::~GameOfLife() {
	if (field != NULL) {
		free(field);
	}
}

void GameOfLife::initialize(Adafruit_WS2801 * strip) {
	uint8_t x, y;
	gameOfLifeRepeats = 0;
	gameOfLifeActiveColor = 0;
	gameOfLifeSetColor = 1;
	for (x = 0; x < STD_ACTIVE_GOF_LEDS; x++) {
		field[random(5)][random(5)] = 1;
	}
}

uint32_t GameOfLife::getModuleColor() {
	return 0xFF0000;
}

void GameOfLife::loop(Adafruit_WS2801 * strip, uint8_t loopCounter, uint8_t right, uint8_t left){
	uint8_t x, y, r, l;
	for (x = 0; x < STD_TABLE_SIZE; x++) {
		for (y = 0; y < STD_TABLE_SIZE; y++) {
			uint32_t * color = strip->getPixelColor(x, y);
			if (!field[x][y]) {
				if (color[0] > 0) {
					color[0] = color[0] - 1;
				}
				if (color[1] > 0) {
					color[1] = color[1] - 1;
				}
				if (color[2] > 0) {
					color[2] = color[2] - 1;
				}
			} else {
				if (color[gameOfLifeActiveColor] != STD_COLOR_REFRESH) {
					color[gameOfLifeActiveColor] += 2;
				}
			}
			strip->setPixelColor(x, y, color[0], color[1], color[2]);
		}
	}
	gameOfLifeSetColor = 0;
	if (loopCounter % 64 == 0) {
		gameOfLifeRepeats++;
		gameOfLifeSetColor = 1;
		for (x = 0; x < STD_TABLE_SIZE; x++) {
			for (y = 0; y < STD_TABLE_SIZE; y++) {
				field[x][y] = 0;
			}
		}
		for (x = 0; x < STD_ACTIVE_GOF_LEDS; x++) {
			field[random(5)][random(5)] = 1;
		}
	}
	if (gameOfLifeRepeats == 4) {
		gameOfLifeRepeats = 0;
		gameOfLifeActiveColor = (gameOfLifeActiveColor + 1) % 3;
	}
}
