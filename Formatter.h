#pragma once
#include "Layer.h"

class Formatter {
protected:
	Layer pixels;
	int channels = 0;
public:
	virtual void parse(ifstream* img) = 0;
	virtual void write(ofstream& outFile, int w, int h) = 0;
	virtual void remake() = 0;
	
	size_t getHeight() {
		return pixels.size();
	}

	size_t getWidth() {
		return pixels[0].size();
	}

	void setLayer(Layer l) {
		pixels = l;
	}

	Layer getLayer() {
		return pixels;
	}
};