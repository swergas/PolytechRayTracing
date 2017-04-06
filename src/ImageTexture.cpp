#include "ImageTexture.h"

ImageTexture::ImageTexture(std::string file_name) {
	_image = new Image(2, 2);
	_image->readReversePPM(file_name);
}

ImageTexture::~ImageTexture() {
}

Color ImageTexture::value(const Vector2 &uv, const Vector3 &p) const {

	float u = uv[0] - int(uv[0]);
	float v = uv.get_y() - int(uv.get_y());

	u *= (_image->_width - 3);
	v *= (_image->_height - 3);

	int iu = (int) u;
	int iv = (int) v;

	float tu = u - iu;
	float tv = v - iv;

	Color c = _image->getPixel(iu, iv) * (1 - tu) * (1 - tv) +
			_image->getPixel(iu + 1, iv) * tu * (1 - tv) +
			_image->getPixel(iu, iv + 1) * (1 - tu) * tv +
			_image->getPixel(iu + 1, iv + 1) * tu * tv;

	return c;
}
