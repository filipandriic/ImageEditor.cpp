#pragma once
#include "BasicOperation.h"
#include <map>

class CompositeOperation {
private:
	vector<pair<int, int>> composite;
	Operation* op;

public:

	void addOperation(int operation, int constant) {
		composite.push_back(pair<int, int>(operation, constant));
	}

	vector<pair<int, int>> getOperations() {
		return composite;
	}

	void finish(Pixel& p) {
		op = new BasicOperation();
		for (pair<int, int> myPair : composite) {
			switch (myPair.first) {
			case 1:
				op->addition(p, myPair.second);
				break;

			case 2:
				op->subtraction(p, myPair.second);
				break;

			case 3:
				op->inverseSubtraction(p, myPair.second);
				break;

			case 4:
				op->multiplication(p, myPair.second);
				break;

			case 5:
				op->division(p, myPair.second);
				break;

			case 6:
				op->inverseDivision(p, myPair.second);
				break;

			case 7:
				op->Power(p, myPair.second);
				break;

			case 8:
				op->Log(p, myPair.second);
				break;

			case 9:
				op->Abs(p, myPair.second);
				break;

			case 10:
				op->Min(p, myPair.second);
				break;

			case 11:
				op->Max(p, myPair.second);
				break;

			case 12:
				op->setPixelBlackWhite(p);
				break;

			case 13:
				op->setPixelGray(p);
				break;
			}




		}
	}
};