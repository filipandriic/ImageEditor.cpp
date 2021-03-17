#include "BitMap.h"

void BitMap::parse(ifstream* img) {
	img->read((char*)&fileHeader, sizeof(fileHeader));
	if (fileHeader.fileType != 0x4D42) {
		cout << "Pogresan format." << endl;
		exit(0);
	}

	img->read((char*)&infoHeader, sizeof(infoHeader));
	channels = infoHeader.bitCount / 8;
	if (infoHeader.bitCount == 32) {
		img->read((char*)&colorHeader, sizeof(colorHeader));
	}
	img->seekg(fileHeader.offset, img->beg);
	
	pixels.resize(infoHeader.height);
	
	if (infoHeader.width % 4 == 0) {
		for (int i = 0; i < pixels.size(); i++) {
			pixels[i].resize(infoHeader.width);
			for (int j = 0; j < pixels[i].size(); j++) {
				img->read((char*)&pixels[i][j], channels);
			}
		}
	}
	else {
		int row = infoHeader.width * channels;
		int temp = row;
		while (temp % 4 != 0) {
			temp++;
		}
		vector<uint8_t> zeroes(temp - row);

		for (int i = 0; i < pixels.size(); i++) {
			pixels[i].resize(infoHeader.width);
			for (int j = 0; j < pixels[i].size(); j++) {
				img->read((char*)&pixels[i][j], channels);
			}
			img->read((char*)zeroes.data(), zeroes.size());
		}
	}
	if (channels == 3)
		remake();
}

void BitMap::remake() {
	infoHeader.size = sizeof(BMPInfoHeader) + sizeof(BMPColorHeader);
	fileHeader.offset = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + sizeof(BMPColorHeader);
	fileHeader.fileSize = fileHeader.offset + infoHeader.height * infoHeader.width;
	infoHeader.bitCount = 32;
	infoHeader.compression = 3;
}

void BitMap::write(ofstream& outFile, int w, int h) {
	infoHeader.width = w;
	infoHeader.height = h;
	fileHeader.fileSize = fileHeader.offset + infoHeader.height * infoHeader.width;
	infoHeader.sizeImage = infoHeader.height * infoHeader.width;
	infoHeader.bitCount = 32;
	fileHeader.offset = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + sizeof(BMPColorHeader);
	infoHeader.compression = 3;
	infoHeader.size = sizeof(BMPInfoHeader) + sizeof(BMPColorHeader);
	outFile.write((const char*)&fileHeader, sizeof(fileHeader));
	outFile.write((const char*)&infoHeader, sizeof(infoHeader));
	outFile.write((const char*)&colorHeader, sizeof(colorHeader));
	for (int i = 0; i < pixels.size(); i++) {
		for (int j = 0; j < pixels[i].size(); j++) {
			outFile.write((const char*)&pixels[i][j], 4);
		}
	}
}