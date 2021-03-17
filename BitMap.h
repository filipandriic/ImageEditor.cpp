#pragma once
#include "Formatter.h"

#pragma pack(push, 1)

struct BMPFileHeader {
	uint16_t fileType = 0x4D42;
	uint32_t fileSize;
	uint16_t reserved1;
	uint16_t reserved2;
	uint32_t offset;
};



struct BMPInfoHeader {
	uint32_t size;
	int32_t width;
	int32_t height;
	uint16_t planes = 1;
	uint16_t bitCount;
	uint32_t compression;
	uint32_t sizeImage;
	int32_t x_resolution;
	int32_t y_resolutin;
	uint32_t colors;
	uint32_t colorsImportant;
};

struct BMPColorHeader {
	uint32_t redMask = 0x00ff0000;
	uint32_t greenMask = 0x0000ff00;
	uint32_t blueMask = 0x000000ff;
	uint32_t alphaMask = 0xff000000;
	uint32_t colorSpaceType = 0x73524742;
	uint32_t unused[16]{ 0 };
};

#pragma pack(pop)

class BitMap : public Formatter {
private:
	BMPFileHeader fileHeader;
	BMPInfoHeader infoHeader;
	BMPColorHeader colorHeader;

public:
	BitMap(ifstream* img) {
		parse(img);
	}

	BitMap(Layer l) {
		pixels = l;
	}

	void parse(ifstream* img) override;

	void remake() override;

	void write(ofstream& outFile, int w, int h) override;

};