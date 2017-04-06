#ifndef SIMPLETEXTURE_H_
#define SIMPLETEXTURE_H_

#include "Texture.h"

class SimpleTexture : Texture {
public:
	Color _color;

	SimpleTexture(const Color &color = 0);
	virtual ~SimpleTexture();

	virtual Color value(const Vector2 &uv, const Vector3 &p) const;
};

#endif /* SIMPLETEXTURE_H_ */
