#include <cassert>

#include "Image.h"

Image::Image(int width, int height) :
	_width(width), _height(height) {
	this->_data = new Color*[this->_width];
	for (int x = 0; x < this->_width; x++) {
		this->_data[x] = new Color[this->_height];
	}
}

Image::Image(int width, int height, Color color) {
	this->_width = width;
	this->_height = height;
	assert (this->_width > 0 && this->_height > 0);

	this->_data = new Color*[this->_width];
	assert(this->_data != 0);

	for (int x = 0; x < this->_width; x++) {
		this->_data[x] = new Color[this->_height];
		assert(_data[x]);
		for (int y = 0; y < this->_height; y++) {
			this->_data[x][y] = color;
		}
	}
}

Image::Image(const Image *source) {
	this->_width = source->_width;
	this->_height = source->_height;

	this->_data = new Color*[this->_width];
	for (int x = 0; x < this->_width; x++) {
		this->_data[x] = new Color[this->_height];
		for (int y = 0; y < this->_height; y++) {
			this->_data[x][y] = source->getPixel(x, y);
		}
	}
}

Image::~Image() {
}

void Image::setPixel(int x, int y, Color color) {
	if (x >= 0 && x < this->_width && y >= 0 && y < this->_height) {
		this->_data[x][y] = color;
	}
}

Color Image::getPixel(int x, int y) const {
	x = (x >= 0 ? x : 0);
	x = (x < this->_width ? x : this->_width - 1);
	y = (y >= 0 ? y : 0);
	y = (y < this->_height ? y : this->_height - 1);
	return this->_data[x][y];
}

bool operator==(const Image &image1, const Image &image2) {
	int width1 = image1._width;
	int h1 = image1._height;
	int width2 = image1._width;
	int h2 = image1._height;
	if (width1 != width2 || h1 != h2) {
		return false;
	} else {
		for (int y = 0; y < h1; y++) {
			for (int x = 0; x < width1; x++) {
				if (image1._data[x][y] != image2._data[x][y]) {
					return false;
				}
			}
		}
	}
	return true;
}

bool operator!=(const Image &image1, const Image &image2) {
	return !(image1 == image2);
}

void Image::writePPM(std::ostream &s) const {
	s << "P6\n" << this->_width << " " << this->_height << "\n255\n";
	unsigned int i;
	for (int y = 0; y < this->_height; y++) {
		for (int x = 0; x < _width; x++) {
			double gamma = 1.0 / 2.2;
			this->_data[x][y] = Color(pow(this->_data[x][y][0], gamma), pow(this->_data[x][y][1],
					gamma), pow(this->_data[x][y][2], gamma));
			i = (unsigned int) (256.0 * this->_data[x][y][0]);
			if (i > 255)
				i = 255;
			s.put((unsigned char) i);
			i = (unsigned int) (256.0 * this->_data[x][y][1]);
			if (i > 255)
				i = 255;
			s.put((unsigned char) i);
			i = (unsigned int) (256.0 * this->_data[x][y][2]);
			if (i > 255)
				i = 255;
			s.put((unsigned char) i);
		}
	}
}

void Image::readPPM(std::string file_name) {
	std::ifstream in;
	in.open(file_name.c_str());
	if (!in.is_open()) {
		std::cerr << "Can't open file \'" << file_name << "\'" << std::endl;
		exit(-1);
	}

	char ch, type;
	char red, green, blue;
	int x, y, cols, rows;
	int num;

	in.get(ch);
	in.get(type);
	in >> cols >> rows >> num;

	this->_width = cols;
	this->_height = rows;

	this->_data = new Color*[this->_width];
	for (x = 0; x < this->_width; x++) {
		this->_data[x] = new Color[this->_height];
	}

	in.get(ch);

	for (y = 0; y < this->_height; y++) {
		for (x = 0; x < this->_width; x++) {
			in.get(red);
			in.get(green);
			in.get(blue);
			this->_data[x][y] = Color(
					(float) ((unsigned char)red)/255.0,
					(float) ((unsigned char)green)/255.0,
					(float) ((unsigned char)blue)/255.0);
		}
	}
}

void Image::readReversePPM(std::string file_name) {
	std::ifstream in;
	in.open(file_name.c_str());
	if (!in.is_open()) {
		std::cerr << "Can't open file \'" << file_name << "\'." << std::endl;
		exit(-1);
	}

	char ch, type;
	char red, green, blue;
	int x, y, cols, rows;
	int num;

	in.get(ch);
	in.get(type);
	in >> cols >> rows >> num;

	this->_width = cols;
	this->_height = rows;

	this->_data = new Color*[this->_width];
	for (x = 0; x < this->_width; x++) {
		this->_data[x] = new Color[this->_height];
	}

	in.get(ch);

	for (y = this->_height-1; y >= 0; y--) {
		for (x = 0; x < this->_width; x++) {
			in.get(red);
			in.get(green);
			in.get(blue);
			this->_data[x][y] = Color(
					(float) ((unsigned char)red)/255.0,
					(float) ((unsigned char)green)/255.0,
					(float) ((unsigned char)blue)/255.0);
		}
	}
}

void Image::printImage(const char *fileName) const {
	std::ofstream myfile;
	myfile.open(fileName);
	this->writePPM(myfile);
	myfile.close();
}
