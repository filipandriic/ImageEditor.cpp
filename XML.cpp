#include "XML.h"


void XML::exportComposite(CompositeOperation* op) {
	XMLDocument outputFile;
	XMLNode* root = outputFile.NewElement("Root");
	outputFile.InsertFirstChild(root);

	XMLElement* comp = outputFile.NewElement("CompositeOperation");	

	for (pair<int, int> myPair : op->getOperations()) {
		XMLElement* operation = outputFile.NewElement("Operation");
		operation->SetAttribute("Number", myPair.first);
		operation->SetAttribute("Constant", myPair.second);

		comp->InsertEndChild(operation);
	}
	root->InsertEndChild(comp);

	string fileName;
	cout << "Unesi ime fajla: " << endl;
	cin >> fileName;
	outputFile.SaveFile(fileName.c_str());
}



void XML::exportProject(Image* img, CompositeOperation* op) {
	XMLDocument outputFile;
	int choice;

	XMLNode* root = outputFile.NewElement("Root");
	outputFile.InsertFirstChild(root);

	XMLElement* finalPic = outputFile.NewElement("FinalPicture");
	finalPic->SetAttribute("WIDTH", img->getPic().getWidth());
	finalPic->SetAttribute("HEIGHT", img->getPic().getHeight());
	root->InsertEndChild(finalPic);

	cout << "Koji format zelite za finalnu sliku?" << endl;
	cout << "1. BMP format." << endl << "2. PAM format" << endl << "Vas izbor? ";
	cin >> choice;

	img->exportPic(choice);

	XMLElement* layers = outputFile.NewElement("Layers");

	for (Layer l : img->getLayers()) {
		XMLElement* myLayer = outputFile.NewElement("Layer");
		myLayer->SetAttribute("Name", l.getName().c_str());
		myLayer->SetAttribute("WIDTH", l.getWidth());
		myLayer->SetAttribute("HEIGHT", l.getHeight());
		
		layers->InsertEndChild(myLayer);
	}

	root->InsertEndChild(layers);

	XMLElement* selections = outputFile.NewElement("Selections");

	for (Selection s : img->getSelections()) {

		XMLElement* mySelection = outputFile.NewElement("Selection");
		for (Rectangle r : s.getRectangles()) {
			XMLElement* myR = outputFile.NewElement("Rectangle");
			myR->SetAttribute("WIDTH", r.getWidth());
			myR->SetAttribute("HEIGHT", r.getHeight());
			myR->SetAttribute("X", r.getPosition().second);
			myR->SetAttribute("Y", r.getPosition().first);

			mySelection->InsertEndChild(myR);
		}

		mySelection->SetAttribute("Name", s.getName().c_str());
		mySelection->SetAttribute("ACTIVE", s.isActive());
		selections->InsertEndChild(mySelection);
	}

	root->InsertEndChild(selections);

	XMLElement* comp = outputFile.NewElement("CompositeOperation");

	for (pair<int, int> myPair : op->getOperations()) {
		XMLElement* operation = outputFile.NewElement("Operation");
		operation->SetAttribute("Number", myPair.first);
		operation->SetAttribute("Constant", myPair.second);

		comp->InsertEndChild(operation);
	}
	root->InsertEndChild(comp);

	string fileName;
	cout << "Unesi ime fajla: " << endl;
	cin >> fileName;
	outputFile.SaveFile(fileName.c_str());
}


CompositeOperation* XML::importComposite() {
	CompositeOperation* ret = new CompositeOperation();
	XMLDocument inputFile;
	string fileName;
	cout << "Unesi ime fajla: " << endl;
	cin >> fileName;
	inputFile.LoadFile(fileName.c_str());

	XMLNode* nothing = inputFile.FirstChild();

	XMLNode* root = inputFile.FirstChild();
	if (root == nullptr) {
		cout << "Greska." << endl;
		exit(0);
	}
	XMLElement* comp = root->FirstChildElement("CompositeOperation");
	XMLElement* operation = comp->FirstChildElement("Operation");

	while (operation) {
		int numOfOp, constant;

		operation->QueryIntAttribute("Number", &numOfOp);
		operation->QueryIntAttribute("Constant", &constant);
		ret->addOperation(numOfOp, constant);
		operation = operation->NextSiblingElement("Operation");
	}

	return ret;
}

Image XML::importProject(CompositeOperation* op) {
	Image img;
	XMLDocument inputFile;
	string fileName;
	cout << "Unesi ime fajla: " << endl;
	cin >> fileName;
	inputFile.LoadFile(fileName.c_str());


	XMLNode* nothing = inputFile.FirstChild();

	XMLNode* root = inputFile.FirstChild();
	if (root == nullptr) {
		cout << "Greska." << endl;
		exit(0);
	}

	int w, h;
	XMLElement* finalPic = root->FirstChildElement("FinalPicture");
	finalPic->QueryIntAttribute("WIDTH", &w);
	finalPic->QueryIntAttribute("HEIGHT", &h);
	img.setWidth(w);
	img.setHeight(h);
	
	const char* layerName;
	XMLElement* layers = root->FirstChildElement("Layers");
	XMLElement* layer = layers->FirstChildElement("Layer");
	while (layer) {
		layerName = layer->Attribute("Name");
		img.addLayer(layerName);
		
		layer = layer->NextSiblingElement("Layer");
	}

	bool active;
	const char* selectionName;
	
	XMLElement* selections = root->FirstChildElement("Selections");
	XMLElement* selection = selections->FirstChildElement("Selection");
	while (selection) {
		vector <Rectangle> vr;
		Rectangle* r;
		selectionName = selection->Attribute("Name");
		selection->QueryBoolAttribute("ACTIVE", &active);

		int x, y, w, h;
		XMLElement* myR = selection->FirstChildElement("Rectangle");
		while (myR) {
			myR->QueryIntAttribute("WIDTH", &w);
			myR->QueryIntAttribute("HEIGHT", &h);
			myR->QueryIntAttribute("X", &x);
			myR->QueryIntAttribute("Y", &y);

			
			r = new Rectangle(x, y, w, h);
			vr.push_back(*r);
			myR = myR->NextSiblingElement("Rectangle");
		}
		Selection s(selectionName, vr, active);
		img.addInSelectionVector(s);
		selection = selection->NextSiblingElement("Selection");
	}

	XMLElement* comp = root->FirstChildElement("CompositeOperation");
	XMLElement* operation = comp->FirstChildElement("Operation");

	while (operation) {
		int numOfOp, constant;

		operation->QueryIntAttribute("Number", &numOfOp);
		operation->QueryIntAttribute("Constant", &constant);
		op->addOperation(numOfOp, constant);
		operation = operation->NextSiblingElement("Operation");
	}

	return img;
}