#pragma once
#include "Operation.h"

class BasicOperation : public Operation {
public:
	void addition(Pixel& p, int x) override {
		p.setPixel(p.getR() + x, p.getG() + x, p.getB() + x, p.getA());
	}
	void subtraction(Pixel& p, int x) override {
		p.setPixel(p.getR() - x, p.getG() - x, p.getB() - x, p.getA());
	}
	void inverseSubtraction(Pixel& p, int x) override {
		p.setPixel(x - p.getR(), x - p.getG(), x - p.getB(), p.getA());
	}
	void multiplication(Pixel& p, int x) override {
		p.setPixel(p.getR() * x, p.getG() * x, p.getB() * x, p.getA());
	}
	void division(Pixel& p, int x) override {
		p.setPixel(p.getR() / x, p.getG() / x, p.getB() / x, p.getA());
	}
	void inverseDivision(Pixel& p, int x) override {
		p.setPixel(x / p.getR(), x / p.getG(), x / p.getB(), p.getA());
	}
	void Power(Pixel& p, int x) override {
		p.setPixel(pow(p.getR(), x), pow(p.getG(), x), pow(p.getB(), x), p.getA());
	}
	void Log(Pixel& p, int) override {
		p.setPixel(log(p.getR()), log(p.getG()), log(p.getB()), p.getA());
	}
	void Abs(Pixel& p, int) override {
		p.setPixel(abs(p.getR()), abs(p.getG()), abs(p.getB()), p.getA());
	}
	void Min(Pixel& p, int x) override {
		uint8_t R = min(x, (int)p.getR());
		uint8_t G = min(x, (int)p.getG());
		uint8_t B = min(x, (int)p.getB());
		p.setPixel(R, G, B, p.getA());
	}
	void Max(Pixel& p, int x) override {
		uint8_t R = max(x, (int)p.getR());
		uint8_t G = max(x, (int)p.getG());
		uint8_t B = max(x, (int)p.getB());
		p.setPixel(R, G, B, p.getA());
	}

	int ArithmeticMiddle(Pixel p) {
		return (p.getR() + p.getG() + p.getB()) / 3;
	}

	uint8_t mediana(vector<uint8_t> vec) {
		if (vec.size() % 2 != 0)
			return vec[vec.size() / 2];
		return (vec[(vec.size() - 1) / 2] + vec[vec.size() / 2]) / 2;
	}

	void setPixelGray(Pixel& p) {
		int arMiddle = ArithmeticMiddle(p);
		p.setPixel(arMiddle, arMiddle, arMiddle, p.getA());
	}



	void getMediana(Pixel& p, Pixel* p1, Pixel* p2, Pixel* p3 = nullptr, Pixel* p4 = nullptr) {

		vector<uint8_t> R;
		vector<uint8_t> G;
		vector<uint8_t> B;

		if (p3 == nullptr && p4 == nullptr) {
			R = { p.getR(), p1->getR(), p2->getR() };
			G = { p.getG(), p1->getG(), p2->getG() };
			B = { p.getB(), p1->getB(), p2->getB() };
		}
		else {
			if (p4 == nullptr) {
				R = { p.getR(), p1->getR(), p2->getR(), p3->getR() };
				G = { p.getG(), p1->getG(), p2->getG(), p3->getG() };
				B = { p.getB(), p1->getB(), p2->getB(), p3->getB() };
			}
			else {
				R = { p.getR(), p1->getR(), p2->getR(), p3->getR(), p4->getR() };
				G = { p.getG(), p1->getG(), p2->getG(), p3->getG(), p4->getG() };
				B = { p.getB(), p1->getB(), p2->getB(), p3->getB(), p4->getB() };
			}
		}

		if (R[0] != R[1] || R[0] != R[2])
			int a = 100;

		sort(R.begin(), R.end());
		sort(G.begin(), G.end());
		sort(B.begin(), B.end());

		p.setPixel(mediana(R), mediana(G), mediana(B), p.getA());
	}

	void setPixelBlackWhite(Pixel& p) {
		int arMiddle = ArithmeticMiddle(p);
		if (arMiddle > 127)
			p.setPixel(0, 0, 0, p.getA());
		else
			p.setPixel(255, 255, 255, p.getA());
	}
};