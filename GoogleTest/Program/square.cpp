#include "square.h"

Square::Square(){
	length = 0;
}

int Square::getLength(){
	return length;
}

void Square::setLength(int sideLength){
	length = sideLength;
}

int Square::getPeremeter(){
	return length * 4;
}

int Square::getArea(){
	return length * length;
}
