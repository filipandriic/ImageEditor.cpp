#pragma once
#include "Pixel.h"

class Rectangle {
private:
	int width;
	int height;
	pair<int, int> position;
	
	

public:
	Rectangle(int x, int y, int w, int h) {
		position.first = y;
		position.second = x;
		width = w;
		height = h;
	}

	int getWidth() {
		return width;
	}

	int getHeight() {
		return height;
	}

	pair<int, int> getPosition() {
		return position;
	}

};