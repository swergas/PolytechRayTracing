#ifndef UVSPHERE_H_
#define UVSPHERE_H_

#include "Sphere.h"
#include "Texture.h"
#include "SimpleTexture.h"

class UVSphere : public Sphere {
public:
	Texture *_tex;
	float _plusTheta, _plusPhi;

	UVSphere(const Color &color = 0, const Material &material = 0, const Vector3 &center = 0, float radius = 0, Texture *tex = new SimpleTexture(), const float plusTheta = 0, const float plusPhi = 0);
	virtual ~UVSphere();

	virtual Color getColor(const Vector3& ptIntersect);
};

#endif /* UVSPHERE_H_ */
