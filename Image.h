#pragma once

#include "PAM.h"
#include "BitMap.h"
#include "XML.h"
#include "Selection.h"

class BitMap;
class Image {
private:
	ifstream* img = nullptr;
	Formatter* formatter;
	int height = 0;
	int width = 0;
	vector<Layer> layers;
	vector<Selection> selections;

	Layer picture;

public:


	vector<Layer> getLayers() {
		return layers;
	}
	void addLayer(string fileName);
	void deleteLayer(int i);
	void addSelection(string name, bool active);
	void format(string fileName);
	void exportPic(int choice);
	void makeBlackAndWhite();
	void makeGreyScale();
	void inversePic();
	void mediana();
	void finishComposite(CompositeOperation* op);
	vector<Selection> getSelections() {
		return selections;
	}
	void addInSelectionVector(Selection s) {
		selections.push_back(s);
	}
	void exportXML(CompositeOperation* op);
	void importXML(CompositeOperation* op);
	
	void setWidth(int width_) {
		width = width_;
	}
	void setHeight(int height_) {
		height = height_;
	}

	Layer getPic() {
		return picture;
	}
	void setPic(Layer l) {
		picture = l;
	}
	void fillRegion(uint8_t R, uint8_t G, uint8_t B);

	void makePic();
	void writePic(string fileName, Formatter* forExport);
	void deleteSelection(string name);
};
