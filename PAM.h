#pragma once
#include "Formatter.h"
#include <regex>

class PAM : public Formatter {
private:
	string fileType = "P7";
	int width;
	int height;
	int depth = 4;
	int maxval = 255;
	string tupltype = "RGB_ALPHA";


public:
	PAM(ifstream* img) {
		parse(img);
	}

	PAM(Layer l) {
		pixels = l;
	}
	
	void parse(ifstream* img) override;
	void remake() override;
	void write(ofstream& outFile, int w, int h) override;
};