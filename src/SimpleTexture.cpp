#include "SimpleTexture.h"

SimpleTexture::SimpleTexture(const Color &color) :
	_color(color) {
}

SimpleTexture::~SimpleTexture() {
}

Color SimpleTexture::value(const Vector2 &uv, const Vector3 &p) const {
	return _color;
}
