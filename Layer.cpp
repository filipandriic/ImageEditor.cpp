#include "Layer.h"

void Layer::BlackAndWhite(Rectangle* r) {
	int h, w, x, y;
	if (r == nullptr) {
		h = pixels.size();
		w = pixels[0].size();
		x = 0;
		y = 0;
	}
	else {
		h = r->getHeight() + r->getPosition().first;
		w = r->getWidth() + r->getPosition().second;
		x = r->getPosition().second;
		y = r->getPosition().first;
	}

	op = new BasicOperation();
	for (int i = y; i < h; i++) {
		for (int j = x; j < w; j++) {
			op->setPixelBlackWhite(pixels[i][j]);
		}
	}
}

void Layer::GreyScale(Rectangle* r) {
	int h, w, x, y;
	if (r == nullptr) {
		h = pixels.size();
		w = pixels[0].size();
		x = 0;
		y = 0;
	}
	else {
		h = r->getHeight() + r->getPosition().first;
		w = r->getWidth() + r->getPosition().second;
		x = r->getPosition().second;
		y = r->getPosition().first;
	}

	op = new BasicOperation();
	for (int i = y; i < h; i++) {
		for (int j = x; j < w; j++) {
			op->setPixelGray(pixels[i][j]);
		}
	}
}

void Layer::Composite(CompositeOperation* op, Rectangle* r) {
	int h, w, x, y;
	if (r == nullptr) {
		h = pixels.size();
		w = pixels[0].size();
		x = 0;
		y = 0;
	}
	else {
		h = r->getHeight() + r->getPosition().first;
		w = r->getWidth() + r->getPosition().second;
		x = r->getPosition().second;
		y = r->getPosition().first;
	}

	for (int i = y; i < h; i++) {
		for (int j = x; j < w; j++) {
			op->finish(pixels[i][j]);
		}
	}
}

void Layer::inverse(Rectangle* r) {
	int h, w, x, y;
	if (r == nullptr) {
		h = pixels.size();
		w = pixels[0].size();
		x = 0;
		y = 0;
	}
	else {
		h = r->getHeight() + r->getPosition().first;
		w = r->getWidth() + r->getPosition().second;
		x = r->getPosition().second;
		y = r->getPosition().first;
	}

	op = new BasicOperation();
	for (int i = y; i < h; i++) {
		for (int j = x; j < w; j++) {
			op->inverseSubtraction(pixels[i][j], 255);
		}
	}
}

void Layer::makeMediana(Rectangle* r) {
	Layer temp = *this;
	int h, w, i, j;
	if (r == nullptr) {
		h = pixels.size();
		w = pixels[0].size();
		j = 0;
		i = 0;
	}
	else {
		h = r->getHeight() + r->getPosition().first;
		w = r->getWidth() + r->getPosition().second;
		j = r->getPosition().second;
		i = r->getPosition().first;
	}

	op = new BasicOperation();
	for (int y = i; y < h; y++) {
		for (int x = j; x < w; x++) {

			if (x == 0) {
				if (y == 0) {
					op->getMediana(pixels[y][x], &temp[y][x + 1], &temp[y + 1][x]);
				}
				else {
					if (y == pixels.size() - 1) {
						op->getMediana(pixels[y][x], &temp[y][x + 1], &temp[y - 1][x]);
					}
					else {
						op->getMediana(pixels[y][x], &temp[y][x + 1], &temp[y + 1][x], &temp[y - 1][x]);
					}
				}
			}
			else {
				if (x == pixels[y].size() - 1) {
					if (y == 0) {
						op->getMediana(pixels[y][x], &temp[y][x - 1], &temp[y + 1][x]);
					}
					else {
						if (y == pixels.size() - 1) {
							op->getMediana(pixels[y][x], &temp[y][x - 1], &temp[y - 1][x]);
						}
						else {
							op->getMediana(pixels[y][x], &temp[y][x - 1], &temp[y + 1][x], &temp[y - 1][x]);
						}
					}
				}
				else {
					if (y == 0) {
						op->getMediana(pixels[y][x], &temp[y][x - 1], &temp[y][x + 1], &temp[y + 1][x]);
					}
					else {
						if (y == pixels.size() - 1) {
							op->getMediana(pixels[y][x], &temp[y][x - 1], &temp[y][x + 1], &temp[y - 1][x]);
						}
						else {
							op->getMediana(pixels[y][x], &temp[y][x - 1], &temp[y][x + 1], &temp[y - 1][x], &temp[y + 1][x]);
						}
					}
				}



			}



		}
	}
}

void Layer::ChangeTransparency(uint8_t A) {
	for (int x = 0; x < pixels[0].size(); x++) {
		for (int y = 0; y < pixels.size(); y++) {
			pixels[y][x].setPixel(pixels[y][x].getR(), pixels[y][x].getG(), pixels[y][x].getB(), A);
		}
	}
}

void Layer::fillRegion(uint8_t R, uint8_t G, uint8_t B, Rectangle* r) {
	for (int x = 0; x < pixels[0].size(); x++) {
		for (int y = 0; y < pixels.size(); y++) {
			pixels[y][x].setPixel(R, G, B);
		}
	}
}