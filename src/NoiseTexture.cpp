#include "NoiseTexture.h"

NoiseTexture::NoiseTexture(float scale) :
	_scale(scale) {
	_c0 = Color(0.8, 0.0, 0.0);
	_c1 = Color(0.0, 0.0, 0.8);
}

NoiseTexture::NoiseTexture(const Color &c0, const Color &c1, float scale) : _scale(scale), _c0(c0), _c1(c1) {
}

NoiseTexture::~NoiseTexture() {
}

Color NoiseTexture::value(const Vector2 &uv, const Vector3 &p) const {
	float t = (1.0f + _solidNoise.noise(p * _scale)) / 2.0f;
	return t * _c0 + (1.0f - t) * _c1;
}
