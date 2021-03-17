#include "Image.h"

int main(int argc, char** argv) {

	int choice;
	Image i;
	string fileName;
	bool active;
	CompositeOperation* op = new CompositeOperation();
	XML myXML;

	while (true) {

		cout << endl << endl << "--------MENU--------" << endl << "1. Unesi sloj." << endl << "2. Obrisi sloj." <<
			endl << "3. Obrada slike." << endl << "4. Eksportuj sliku." << endl << "5. Dodaj selekciju." << endl << "6. Obrisi selekciju." <<
			endl << "7. Kompozitna funkcija." << endl << "8. Eksportuj projekat." << endl << "9. Importuj projekat." <<
			endl << "0. Izadji iz programa" << endl << "Vas izbor? ";
		cin >> choice;
		switch (choice) {
		case 1:
			cout << "Kako se slika zove? ";
			cin >> fileName;
			i.addLayer(fileName);
			break;

		case 2:
			int index;
			cout << "Koji sloj zelite da obrisete? ";
			cin >> index;
			if (index > i.getLayers().size()) {
				cout << "Nece moci. Ajmo ponovo." << endl;
				break;
			}
			i.deleteLayer(index - 1);
			break;

		case 3:
			int choice1;
			cout << endl << endl << "--------OBRADA--------" << endl << "1. Napravi crno-belu sliku." << endl
				<< "2. Napravi sivu sliku." << endl << "3. Ofarbaj sliku." << endl
				<< "4. Inverzija slike." << endl << "5. Medijana piksela." << endl << "Vas izbor? ";
			cin >> choice1;
			switch (choice1) {
			case 1:
				i.makeBlackAndWhite();
				break;

			case 2:
				i.makeGreyScale();
				break;

			case 3:
				uint8_t R;
				uint8_t G;
				uint8_t B;
				cout << "Boje: " << endl;
				cout << "R = ";
				cin >> R;
				cout << "G = ";
				cin >> G;
				cout << "B = ";
				cin >> B;

				i.fillRegion(R, G, B);
				break;

			case 4:
				i.inversePic();
				break;

			case 5:
				i.mediana();
				break;
			}
			break;

		case 4:
			cout << "1. BMP format." << endl << "2. PAM format" << endl << "Vas izbor? ";
			cin >> choice;

			i.exportPic(choice);
			
			break;

		case 5:
			cout << "Ime selekcije? ";
			cin >> fileName;
			cout << "Aktivna?" << endl << "1 - Aktivna." << endl << "0 - Neaktivna" << endl << "Unesi. ";
			cin >> active;
			i.addSelection(fileName, active);
			break;

		case 6:
			cout << "Ime selekcije? ";
			cin >> fileName;
			i.deleteSelection(fileName);
			break;

		case 7:
			int choice2, choice3;
			while (true) {
				cout << "----KOMPOZITNA FUNKCIJA----" << endl;
				cout << "1. Napravi svoju kompozitnu funkciju." << endl <<
					"2. Uvezi kompozitnu funkciju." << endl << "3. Eksportuj kompozitnu funkciju." << endl <<
					"4. Izvrsi kompozitnu funkciju." << endl << "0. Izadji iz kompozitnih funkcija." << endl << "Vas izbor? " << endl;
				cin >> choice3;
				if (choice3 == 0) break;
				switch (choice3) {
				case 1:
					op = new CompositeOperation();

					while (true) {
						cout << endl << "Koje operacije zelite da dodate i sa kojom konstantom?" << endl;
						cout << "1. Sabiranje." << endl << "2. Oduzimanje" << endl
							<< "3. Inverzno oduzimanje." << endl << "4. Mnozenje." << endl
							<< "5. Deljenje" << endl << "6. Inverzno deljenje." << endl
							<< "7. Podizanje na stepen." << endl << "8. Logaritam." << endl
							<< "9. Apsolutna vrednost." << endl << "10. Min." << endl
							<< "11. Max." << endl << "12. Crno-bela." << endl << "13. Siva"
							<< endl << "0. Zavrsi stvaranje kompozitne funkcije" << endl;
						cout << "Vas izbor? ";
						cin >> choice2;
						if (choice2 == 0) {
							break;
						}

						int constant;
						cin >> constant;
						op->addOperation(choice2, constant);
					}
					break;
					
					
				case 2:
					op = new CompositeOperation();
					op = myXML.importComposite();
					break;

				case 3:
					
					myXML.exportComposite(op);
					break;

				case 4:
					i.finishComposite(op);
					break;

				}		
			}


			break;

		case 8:
			i.exportXML(op);
			break;

		case 9:
			op = new CompositeOperation();
			i.importXML(op);
			break;

		case 0:
			exit(0);
			break;
		}
	}
}