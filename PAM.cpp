#include "PAM.h"

void PAM::parse(ifstream* img) {
	string textLine;

	getline(*img, fileType);

	if (fileType != "P7") {
		cout << "Pogresan format." << endl;
		exit(0);
	}

	regex rx1("[^0-9]*([0-9]*)");
	getline(*img, textLine);
	smatch result;
	if (regex_match(textLine, result, rx1)) {
		width = atoi(result.str(1).c_str());
	}
	getline(*img, textLine);
	
	if (regex_match(textLine, result, rx1)) {
		height = atoi(result.str(1).c_str());
	}

	getline(*img, textLine);

	if (regex_match(textLine, result, rx1)) {
		depth = atoi(result.str(1).c_str());
	}

	getline(*img, textLine);

	if (regex_match(textLine, result, rx1)) {
		maxval = atoi(result.str(1).c_str());
	}

	getline(*img, textLine);
	regex rx2("([A-Z]*) ([A-Z]*.*)");
	if (regex_match(textLine, result, rx2)) {
		tupltype = result.str(2).c_str();
	}
	getline(*img, textLine);
	channels = depth;

	pixels.resize(height);

	if (width % 4 == 0) {
		for (int i = pixels.size() - 1; i >= 0; i--) {
			pixels[i].resize(width);
			for (int j = 0; j < pixels[i].size(); j++) {
				img->read((char*)&pixels[i][j], channels);
				pixels[i][j].swapRB();
			}
		}
	}
	else {
		int row = width * channels;
		int temp = row;
		while (temp % 4 != 0) {
			temp++;
		}
		vector<uint8_t> zeroes(temp - row);

		for (int i = pixels.size() - 1; i >= 0; i--) {
			pixels[i].resize(width);
			for (int j = 0; j < pixels[i].size(); j++) {
				img->read((char*)&pixels[i][j], channels);
				pixels[i][j].swapRB();
			}
			img->read((char*)zeroes.data(), zeroes.size());
		}
	}
	if (channels != 4)
		remake();
}

void PAM::remake() {
	depth = 4;
	tupltype = "RGB_ALPHA";
}

void PAM::write(ofstream& outFile, int w, int h) {
	width = w;
	height = h;
	outFile << fileType << endl;
	outFile << "WIDTH " << width << endl;
	outFile << "HEIGHT " << height << endl;
	outFile << "DEPTH " << depth << endl;
	outFile << "MAXVAL " << maxval << endl;
	outFile << "TUPLTYPE " << tupltype << endl;
	outFile << "ENDHDR" << endl;

	for (int i = pixels.size() - 1; i >= 0 ; i--) {
		for (int j = 0; j < pixels[i].size(); j++) {
			pixels[i][j].swapRB();
			outFile.write((const char*)&pixels[i][j], 4);
		}
	}
}