#ifndef MARBLETEXTURE_H_
#define MARBLETEXTURE_H_

#include <cmath>
#include "Texture.h"
#include "Color.h"
#include "SolidNoise.h"

class MarbleTexture : public Texture {
public:
	float _freq, _scale;
	int _octaves;
	Color _c0, _c1, _c2;
	SolidNoise _noise;

	MarbleTexture(float stripes_per_unit, float scale = 5.0f, int octaves = 8);
	MarbleTexture(const Color &c0, const Color &c1, const Color &c2, float stripes_per_unit, float scale = 5.0f, int octaves = 8);
	virtual ~MarbleTexture();

	virtual Color value(const Vector2 &uv, const Vector3 &p) const;
};

#endif /* MARBLETEXTURE_H_ */
