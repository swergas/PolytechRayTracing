#ifndef SOLIDNOISE_H_
#define SOLIDNOISE_H_

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include "Vector3.h"
#include "RNG.h"

class SolidNoise {
public:
	Vector3 _grad[16];
	int _phi[16];

	SolidNoise();
	virtual ~SolidNoise();

	float noise(const Vector3 &pt) const;
	float turbulence(const Vector3 &pt, int depth) const;
	float dturbulence(const Vector3 &pt, int depth, float d) const;
	float omega(float t) const;
	Vector3 gamma(int i, int j, int k) const;
	int intGamma(int i, int j) const;
	float knot(int i, int j, int k, Vector3 &v) const;
};

#endif /* SOLIDNOISE_H_ */
