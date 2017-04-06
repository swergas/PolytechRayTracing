#ifndef NOISETEXTURE_H_
#define NOISETEXTURE_H_

#include <cmath>
#include "Texture.h"
#include "Color.h"
#include "SolidNoise.h"

class NoiseTexture : public Texture {
public:
	float _scale;
	Color _c0, _c1;
	SolidNoise _solidNoise;

	NoiseTexture(float scale = 1.0f);
	NoiseTexture(const Color &c0, const Color &c1, float scale = 1.0f);
	virtual ~NoiseTexture();

	virtual Color value(const Vector2 &uv, const Vector3 &p) const;
};

#endif /* NOISETEXTURE_H_ */
