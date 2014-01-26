#include "SPI.h"	
#include "pix-table-arduino.h"

PixTable p = PixTable();

void setup(){
	p.begin();
	p.gameOfLife();
}

void loop()
{
	p.loop();
}