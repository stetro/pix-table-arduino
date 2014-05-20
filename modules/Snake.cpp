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

class Snake: public Module {
	public:
		Snake();
		~Snake();
		uint32_t getModuleColor();
		void loop(Adafruit_WS2801 * strip, uint8_t loopCounter, uint8_t right, uint8_t left);
		void initialize(Adafruit_WS2801 * strip);
	private:
		uint8_t snake[STD_TABLE_SIZE*STD_TABLE_SIZE][3];
		uint8_t apple[2];
		uint8_t direction;
		uint8_t negativeModReduction(uint8_t, uint8_t);
		void reset(Adafruit_WS2801 * strip);
		void setNewApplePosition();
};

Snake::Snake() {
}
Snake::~Snake() {
	if (snake != NULL) {
		free(snake);
	}
}

void Snake::setNewApplePosition(){
	apple[0]=random(STD_TABLE_SIZE);
	apple[1]=random(STD_TABLE_SIZE);
}


void Snake::initialize(Adafruit_WS2801 * strip) {
	snake[0][0]=2;snake[0][1]=0;snake[0][2]=1;
	snake[1][0]=1;snake[1][1]=0;snake[1][2]=1;
	snake[2][0]=0;snake[2][1]=0;snake[2][2]=1;
	snake[3][0]=0;snake[3][1]=0;snake[3][2]=0;
	direction=SNAKE_RIGHT;
	reset(strip);
}

uint32_t Snake::getModuleColor() {
	return 0x00FF00;
}
void Snake::reset(Adafruit_WS2801 * strip){
	uint8_t x, y;
	for (x=0; x < STD_TABLE_SIZE; x++) {
		for (y=0; y < STD_TABLE_SIZE; y++) {
			strip->setPixelColor(x,y,0);
		}
	}
}

void Snake::loop(Adafruit_WS2801 * strip, uint8_t loopCounter, uint8_t right, uint8_t left) {
	uint8_t x, previous[2], i,j;
	// paint snake and apple and detect if game is loosen
	previous[0]=snake[0][0];
	previous[1]=snake[0][1];
	for(x=0;x<STD_TABLE_SIZE*STD_TABLE_SIZE;x++){
		if(snake[x][2] ==1){
			strip->setPixelColor(snake[x][0] ,snake[x][1] ,0x00FF00);
			if(x>0 && snake[x][0]==previous[0] && snake[x][1]==previous[1]){
				initialize(strip);
			}
		}else{
			break;
		}
	}
	strip->setPixelColor(apple[0] ,apple[1] ,0xFF7700);
	// do move
	if(loopCounter % 7 == 0){
		switch(direction){
			case SNAKE_RIGHT:
				snake[0][0] = (snake[0][0] + 1) % STD_TABLE_SIZE;
				break;
			case SNAKE_DOWN:
				snake[0][1] = (snake[0][1] + 1) % STD_TABLE_SIZE;
				break;
			case SNAKE_LEFT:
				snake[0][0] = negativeModReduction(snake[0][0] ,  STD_TABLE_SIZE);
				break;
			case SNAKE_UP:
				snake[0][1] = negativeModReduction(snake[0][1] ,  STD_TABLE_SIZE);
				break;
		}
		for(x=1;x<STD_TABLE_SIZE*STD_TABLE_SIZE;x++){
			if(snake[x][2] == 1){
				i=previous[0];
				j=previous[1];
				previous[0]=snake[x][0];
				previous[1]=snake[x][1];
				snake[x][0]=i;
				snake[x][1]=j;
			}else{
				strip->setPixelColor(previous[0], previous[1], 0);
				break;
			}
		}
	}
	// detect apple
	if(apple[0]==snake[0][0] && apple[1]==snake[0][1]){
		for(x=1;x<STD_TABLE_SIZE*STD_TABLE_SIZE;x++){
			if(snake[x][2] == 0){
				snake[x][2]=1;
				snake[x][0]=snake[x-1][0];
				snake[x][1]=snake[x-1][1];
				snake[x+1][2]=0;
				setNewApplePosition();
				break;
			}
		}
	}
	// do turn
	if(left){
		direction = negativeModReduction(direction,4);
	}
	if(right){
		direction = (direction+1)%4;

	}
}
uint8_t Snake::negativeModReduction(uint8_t a, uint8_t b){
	if(a==0){
		return b-1;
	}else{
		return (a-1)%b;
	}

}
