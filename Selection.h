#pragma once
#include "Rectangle.h"

class Selection {
private:
	bool active;
	string name;
	vector<Rectangle> rectangles;

public:
	Selection(string _name, vector<Rectangle> _rectangles, bool _active) {
		name = _name;
		rectangles = _rectangles;
		active = _active;
	}

	void setActive(bool active_) {
		active = active_;
	}


	bool isActive() {
		return active;
	}

	vector<Rectangle> getRectangles() {
		return rectangles;
	}

	string getName() {
		return name;
	}
};