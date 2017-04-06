#include "MarbleTexture.h"

MarbleTexture::MarbleTexture(float stripes_per_unit, float scale, int octaves) {
	_scale = scale;
	_octaves = octaves;
	_freq = M_PI * stripes_per_unit;
	_c0 = Color(0.8, 0.8, 0.8);
	_c1 = Color(0.4, 0.2, 0.1);
	_c2 = Color(0.06, 0.04, 0.02);
}

MarbleTexture::MarbleTexture(const Color &c0, const Color &c1, const Color &c2,
		float stripes_per_unit, float scale, int octaves) :
	_c0(c0), _c1(c1), _c2(c2) {
	_scale = scale;
	_octaves = octaves;
	_freq = M_PI * stripes_per_unit;
}

MarbleTexture::~MarbleTexture() {
}

Color MarbleTexture::value(const Vector2 &uv, const Vector3 &p) const {
	float temp = _scale * _noise.turbulence(_freq * p, _octaves);
	float t = 2.0f * fabs(sin(_freq * p[0] + temp));

	if (t < 1.0f) {
		return (_c1 * t + (1.0f - t) * _c2);
	} else {
		t -= 1.0f;
		return (_c0 * t + (1.0f - t) * _c1);
	}
}
