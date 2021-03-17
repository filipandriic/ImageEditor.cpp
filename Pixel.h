#pragma once
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

class Pixel {
private:
	uint8_t B;
	uint8_t G;
	uint8_t R;
	uint8_t A = 255;
public:

	Pixel(uint8_t R = 0, uint8_t G = 0, uint8_t B = 0, uint8_t A = 255) {
		this->B = B;
		this->G = G;
		this->R = R;
		this->A = A;
	}

	bool operator!=(Pixel p) {
		if (B != p.getB())
			return true;
		if (G != p.getG())
			return true;
		if (R != p.getR())
			return true;
		if (A != p.getA())
			return true;
		return false;
	}
	
	uint8_t getB() {
		return B;
	}
	uint8_t getG() {
		return G;
	}
	uint8_t getR() {
		return R;
	}
	uint8_t getA() {
		return A;
	}

	void swapRB() {
		swap(R, B);
	}

	void setAlpha(uint8_t alpha) {
		A = alpha;
	}
	
	void setPixel(uint8_t R, uint8_t G, uint8_t B, uint8_t A = 255) {
		this->B = B;
		this->G = G;
		this->R = R;
		this->A = A;
	}
};