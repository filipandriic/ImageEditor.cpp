#include "Image.h"

void Image::format(string fileName) {
	cout << "Formatiranje...";

	if (fileName[fileName.size() - 1] == 'p')
		formatter = new BitMap(img);
	else
		formatter = new PAM(img);
}

void Image::exportPic(int choice) {
	string outFile;
	Formatter* forExport;
	cout << "Kako zelite da se zove slika? ";
	cin >> outFile;
	if (choice == 1)
		forExport = new BitMap(picture);
	else
		forExport = new PAM(picture);

	writePic(outFile, forExport);
}

void Image::makeBlackAndWhite() {
	/*string outFile;
	cout << "Kako zelite da se zove slika? ";
	cin >> outFile;*/
	bool flag = false;


	for (Selection s : selections) {
		if (s.isActive() == true) {
			flag = true;
			for (Rectangle r : s.getRectangles()) {
				Rectangle* myR = &r;
				picture.BlackAndWhite(myR);
			}
		}

	}
	if (flag == false) {
		picture.BlackAndWhite();
	}
}

void Image::makeGreyScale() {
	/*string outFile;
	cout << "Kako zelite da se zove slika? ";
	cin >> outFile;*/
	bool flag = false;
	

	for (Selection s : selections) {
		if (s.isActive() == true) {
			flag = true;
			for (Rectangle r : s.getRectangles()) {
				Rectangle* myR = &r;
				picture.GreyScale(myR);
			}
		}

	}
	if (flag == false) {
		picture.GreyScale();
	}
}

void Image::inversePic() {
	
	bool flag = false;
	

	for (Selection s : selections) {
		if (s.isActive() == true) {
			flag = true;
			for (Rectangle r : s.getRectangles()) {
				Rectangle* myR = &r;
				picture.inverse(myR);
			}
		}

	}
	if (flag == false) {
		picture.inverse();
	}
}

void Image::mediana() {
	
	bool flag = false;
	

	for (Selection s : selections) {
		if (s.isActive() == true) {
			flag = true;
			for (Rectangle r : s.getRectangles()) {
				Rectangle* myR = &r;
				picture.makeMediana(myR);
			}
		}

	}
	if (flag == false) {
		picture.makeMediana();
	}

}

void Image::finishComposite(CompositeOperation* op) {
	bool flag = false;
	for (Selection s : selections) {
		if (s.isActive() == true) {
			flag = true;
			for (Rectangle r : s.getRectangles()) {
				Rectangle* myR = &r;
				picture.Composite(op, myR);
			}
		}

	}
	if (flag == false) {
		picture.Composite(op);
	}
}

void Image::makePic() {
	if (layers.empty()) {
		cout << "Nije ucitana ni jedna slika." << endl;
	}
	else {

		picture = layers[0];

		for (Layer l : layers) {
			if (l != layers[0]) {
				if (picture.getHeight() < height)
					picture.resize(height);
				if (l.getHeight() < height)
					l.resize(height);

				if (picture.getWidth() < width) {
					for (int i = 0; i < picture.getHeight(); i++) {
						int j = picture[i].size();
						picture[i].resize(width);
						for (; j < picture.getWidth(); j++) {
							picture[i][j].setAlpha(0);
						}
					}
				}
				if (l.getWidth() < width) {
					for (int i = 0; i < l.getHeight(); i++) {
						int j = l[i].size();
						l[i].resize(width);
						for (; j < l.getWidth(); j++) {
							l[i][j].setAlpha(0);
						}
					}
				}

				for (int i = 0; i < height; i++) {

					for (int j = 0; j < width; j++) {


						double Azero = (double)picture[i][j].getA() / 255;
						double Aone = (double)l[i][j].getA() / 255;
						double A = Azero + (1 - Azero) * Aone;

						int Rzero = picture[i][j].getR();
						int Gzero = picture[i][j].getG();
						int Bzero = picture[i][j].getB();

						int Rone = l[i][j].getR();
						int Gone = l[i][j].getG();
						int Bone = l[i][j].getB();

						int R = Rzero * Azero / A + Rone * (1 - Azero) * Aone / A;
						int G = Gzero * Azero / A + Gone * (1 - Azero) * Aone / A;
						int B = Bzero * Azero / A + Bone * (1 - Azero) * Aone / A;
						picture[i][j].setPixel(R, G, B, (uint8_t)(A * 255));
					}
				}
			}
		}
	}
}

void Image::addLayer(string fileName) {
	
	img = new ifstream(fileName, ios_base::binary);
	if (!img->is_open()) {
		cout << "Fajl ne postoji." << endl;
	}
	else {
		format(fileName);

		layers.push_back(formatter->getLayer());
		layers[layers.size() - 1].setName(fileName);
		if (height == 0) {
			height = formatter->getHeight();
			width = formatter->getWidth();
		}
		else {
			if (formatter->getHeight() > height)
				height = formatter->getHeight();
			if (formatter->getWidth() > width)
				width = formatter->getWidth();
		}
		makePic();
		cout << " uspesno." << endl;
	}
}

void Image::deleteLayer(int i) {
	if (i > layers.size()) {
		cout << "Lejer ne postoji." << endl;
	}
	else {
		Layer l = layers[i];
		layers.erase(layers.begin() + i);

		if (l.getHeight() == height) {
			height = 0;
			for (Layer temp : layers)
				if (temp.getHeight() > height)
					height = temp.getHeight();
		}
		if (l.getWidth() == width) {
			width = 0;
			for (Layer temp : layers)
				if (temp.getWidth() > width)
					width = temp.getWidth();
		}
		makePic();
	}
}

void Image::writePic(string outName, Formatter* forExport) {
	ofstream outFile(outName, ios_base::binary);

	forExport->write(outFile, width, height);
}

void Image::fillRegion(uint8_t R, uint8_t G, uint8_t B) {
	bool flag = false;

	for (Selection s : selections) {
		if (s.isActive() == true) {
			flag = true;
			for (Rectangle r : s.getRectangles()) {
				Rectangle* myR = &r;
				picture.fillRegion(R, G, B, myR);
			}
		}

	}
	if (flag == false) {
		picture.fillRegion(R, G, B);
	}
}

void Image::addSelection(string name, bool active) {
	vector <Rectangle> vr;
	Rectangle* r;
	int choice = -1;

	while (choice != 0) {
		cout << "1. Napravi pravougaonik i dodaj ga selekciji." << endl << "0. Zavrsi pravljenje selekcije." << endl;
		
		cin >> choice;
		switch (choice) {
		case 1:
			int x, y, w, h;
			cout << "Pozicija(x, y) = ";
			cin >> x >> y;
			cout << "Sirina = ";
			cin >> w;
			cout << "Visina = ";
			cin >> h;

			if ((x < 0) || (y < 0) || (x + w > width) || (y + h > height)) {
				cout << "Invalid input." << endl;
				break;
			}

			r = new Rectangle(x, y, w, h);
			vr.push_back(*r);
			break;

		case 0:
			Selection s(name, vr, active);		
			selections.push_back(s);
			break;
		}
	}
}

void Image::deleteSelection(string name) {
	int i = 0;
	for (Selection s : selections) {
		if (s.getName() == name) {
			selections.erase(selections.begin() + i);
		}
		else {
			i++;
		}
	}
	if (i == selections.size())
		cout << "Selekcija ne postoji." << endl;
}

void Image::exportXML(CompositeOperation* op) {
	XML* myXML = new XML();
	myXML->exportProject(this, op);
}

void Image::importXML(CompositeOperation* op) {
	XML* myXML = new XML();
	*this = myXML->importProject(op);
}