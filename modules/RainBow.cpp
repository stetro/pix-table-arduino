class RainBow: public Module {
	public:
		RainBow();
		~RainBow();
		uint32_t getModuleColor();
		void loop(Adafruit_WS2801 * strip, uint8_t loopCounter, uint8_t right, uint8_t left);
		void initialize(Adafruit_WS2801 * strip);
	private:
		uint8_t rainbowLoopVar;

		uint32_t 
			Color(byte r, byte g, byte b),
			Wheel(byte WheelPos);

};



RainBow::RainBow() {
}

RainBow::~RainBow() {
}

void RainBow::initialize(Adafruit_WS2801 * strip) {
	rainbowLoopVar=0;
}

uint32_t RainBow::getModuleColor() {
	return 0x0000FF;
}

void RainBow::loop(Adafruit_WS2801 * strip, uint8_t loopCounter, uint8_t right, uint8_t left) {
	uint8_t i;
	rainbowLoopVar++;
	for (i=0; i < strip->numPixels(); i++) {
		strip->setPixelColor(i, Wheel( ((i * 256 / strip->numPixels()) + rainbowLoopVar) % 256) );
	}

}

/* Helper functions by Adafruit */
uint32_t RainBow::Color(byte r, byte g, byte b)
{
	uint32_t c;
	c = r;
	c <<= 8;
	c |= g;
	c <<= 8;
	c |= b;
	return c;
}
uint32_t RainBow::Wheel(byte WheelPos)
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
