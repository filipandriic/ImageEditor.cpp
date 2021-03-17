#pragma once
#include "Formatter.h"
#include "tinyxml2.h"
#include "Image.h"

class Image;
using namespace tinyxml2;

class XML : public Formatter {
public:
	void parse(ifstream* img) override {}
	void write(ofstream& outFile, int w, int h) override {}
	void remake() override {}

	void exportComposite(CompositeOperation* op);
	CompositeOperation* importComposite();
	void exportProject(Image* img, CompositeOperation* op);
	Image importProject(CompositeOperation* op);
};