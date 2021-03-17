#pragma once
#include "Pixel.h"
#include <math.h>

class Operation {
public:
	virtual void addition(Pixel& p, int x) = 0;
	virtual void subtraction(Pixel& p, int x) = 0;
	virtual void inverseSubtraction(Pixel& p, int x) = 0;
	virtual void multiplication(Pixel& p, int x) = 0;
	virtual void division(Pixel& p, int x) = 0;
	virtual void inverseDivision(Pixel& p, int x) = 0;

	virtual void Power(Pixel& p, int x) = 0;
	virtual void Log(Pixel& p, int x = 0) = 0;
	virtual void Abs(Pixel& p, int x = 0) = 0;
	virtual void Min(Pixel& p, int x) = 0;
	virtual void Max(Pixel& p, int x) = 0;

	virtual int ArithmeticMiddle(Pixel p) = 0;

	virtual uint8_t mediana(vector<uint8_t> vec) = 0;

	virtual void setPixelGray(Pixel& p) = 0;



	virtual void getMediana(Pixel& p, Pixel* p1, Pixel* p2, Pixel* p3 = nullptr, Pixel* p4 = nullptr) = 0;

	virtual void setPixelBlackWhite(Pixel& p) = 0;
};