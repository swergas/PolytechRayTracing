#include "UVSphere.h"
#include <cmath>

UVSphere::UVSphere(const Color &color, const Material &material, const Vector3 &center, float radius, Texture *tex, const float plusTheta, const float plusPhi) :
	Sphere(color, material, center, radius), _tex(tex), _plusTheta(plusTheta), _plusPhi(plusPhi) {
}

UVSphere::~UVSphere() {
}

Color UVSphere::getColor(const Vector3& ptIntersect) {
	Vector3 n = normal(ptIntersect) / _radius;

	float twopi = 6.28318530718f;
	float theta = acos(n[2]);
	float phi = atan2(n[1], n[0]) + _plusPhi;

	if (phi < 0.0f) {
		phi += twopi;
	}

	float one_over_2pi = .159154943092f;
	float one_over_pi = .318309886184f;

	Vector2 uv(phi * one_over_2pi, (M_PI - theta) * one_over_pi);

	return _tex->value(uv, ptIntersect);
}
