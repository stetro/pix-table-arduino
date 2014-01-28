#include "SPI.h"	
#include "pix-table-arduino.h"

PixTable p = PixTable();
uint8_t right=LOW,prevRight=LOW,left=LOW,prevLeft=LOW;

void setup(){
	p.begin();
	p.menu();
	pinMode(7, INPUT);
	pinMode(6, INPUT);
}

void loop(){
	right = digitalRead(7);
	if(prevRight != right){
		if(right==HIGH){
			p.pushRight();
		}  
		prevRight = right;
	}
	left = digitalRead(6);
	if(prevLeft != left){
		if(left==HIGH){
			p.pushLeft();
		}  
		prevLeft=left;
	}
	p.loop();
}
