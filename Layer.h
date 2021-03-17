#pragma once
#include "CompositeOperation.h"
#include "Rectangle.h"

class Layer {
private:
	vector<vector<Pixel>> pixels;
	Operation* op = nullptr;
	string name;

public:
	vector<Pixel>& operator[](int index) {
		return pixels[index];
	}

	void setName(string s) {
		name = s;
	}

	string getName() {
		return name;
	}

	bool operator!=(Layer l) {
		if (getHeight() != l.getHeight())
			return true;
		if (getWidth() != l.getWidth())
			return true;
		for (int i = 0; i < getHeight(); i++)
			for (int j = 0; j < getWidth(); j++)
				if (pixels[i][j] != l[i][j])
					return true;
		return false;
	}
	
	void resize(size_t i) {
		pixels.resize(i);
	}
	size_t size() {
		return pixels.size();
	}

	size_t getHeight() {
		return pixels.size();
	}

	size_t getWidth() {
		return pixels[0].size();
	}

	void BlackAndWhite(Rectangle* r = nullptr);

	void GreyScale(Rectangle* r = nullptr);

	void inverse(Rectangle* r = nullptr);

	void makeMediana(Rectangle* r = nullptr);

	void ChangeTransparency(uint8_t A);

	void Composite(CompositeOperation* op, Rectangle* r = nullptr);

	void fillRegion(uint8_t R, uint8_t G, uint8_t B, Rectangle* r = nullptr);
};