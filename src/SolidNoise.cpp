#include "SolidNoise.h"

SolidNoise::SolidNoise() {
	RNG random;
	int i;

	_grad[0] = Vector3( 1,  1, 0);
	_grad[1] = Vector3(-1,  1, 0);
	_grad[2] = Vector3( 1, -1, 0);
	_grad[3] = Vector3(-1, -1, 0);

	_grad[4] = Vector3( 1, 0,  1);
	_grad[5] = Vector3(-1, 0,  1);
	_grad[6] = Vector3( 1, 0, -1);
	_grad[7] = Vector3(-1, 0, -1);

	_grad[8] = Vector3(0,  1,  1);
	_grad[9] = Vector3(0, -1,  1);
	_grad[10]= Vector3(0,  1, -1);
	_grad[11]= Vector3(0, -1, -1);

	_grad[12]= Vector3( 1,  1,  0);
	_grad[13]= Vector3(-1,  1,  0);
	_grad[14]= Vector3( 0, -1,  1);
	_grad[15]= Vector3( 0, -1, -1);

	for (i = 0; i < 16; i++) {
		_phi[i] = i;
	}

	//Shuffle phi
	for (i = 14; i >= 0; i--) {
		int target = int(random() * i);
		int temp = _phi[i + 1];
		_phi[i + 1] = _phi[target];
		_phi[target] = temp;
	}
}

SolidNoise::~SolidNoise() {
}

float SolidNoise::noise(const Vector3 &pt) const {
	int fi, fj, fk;
	float fu, fv, fw, sum;
	Vector3 v;

	fi = int(floor(pt[0]));
	fj = int(floor(pt[1]));
	fk = int(floor(pt[2]));
	fu = pt[0] - float(fi);
	fv = pt[1] - float(fj);
	fw = pt[2] - float(fk);
	sum = 0.0;

	v = Vector3(fu, fv, fw);
	sum += knot(fi, fj, fk, v);

	v = Vector3(fu - 1, fv, fw);
	sum += knot(fi + 1, fj, fk, v);

	v = Vector3(fu, fv - 1, fw);
	sum += knot(fi, fj + 1, fk, v);

	v = Vector3(fu, fv, fw - 1);
	sum += knot(fi, fj, fk + 1, v);

	v = Vector3(fu - 1, fv - 1, fw);
	sum += knot(fi + 1, fj + 1, fk, v);

	v = Vector3(fu - 1, fv, fw - 1);
	sum += knot(fi + 1, fj, fk + 1, v);

	v = Vector3(fu, fv - 1, fw - 1);
	sum += knot(fi, fj + 1, fk + 1, v);

	v = Vector3(fu - 1, fv - 1, fw - 1);
	sum += knot(fi + 1, fj + 1, fk + 1, v);

	return sum;
}

float SolidNoise::turbulence(const Vector3 &pt, int depth) const {
	float sum = 0.0f;
	float weight = 1.0f;
	Vector3 ptemp(pt);

	sum = fabs(noise(ptemp));

	for (int i = 1; i < depth; i++) {
		weight *= 2;
		ptemp.setX(pt[0] * weight);
		ptemp.setY(pt[1] * weight);
		ptemp.setZ(pt[2] * weight);

		sum += fabs(noise(ptemp)) / weight;
	}

	return sum;
}

float SolidNoise::dturbulence(const Vector3 &pt, int depth, float d) const {
	float sum = 0.0f;
	float weight = 1.0f;
	Vector3 ptemp(pt);

	sum = fabs(noise(ptemp)) / d;

	for (int i = 1; i < depth; i++) {
		weight *= d;
		ptemp.setX(pt[0] * weight);
		ptemp.setY(pt[1] * weight);
		ptemp.setZ(pt[2] * weight);

		sum += fabs(noise(ptemp)) / d;
	}

	return sum;
}

float SolidNoise::omega(float t) const {
	t = (t > 0.0f) ? t : -t;
	return (-6.0f * t * t * t * t * t + 15.0f * t * t * t * t - 10.0f * t * t * t + 1.0f);
}

Vector3 SolidNoise::gamma(int i, int j, int k) const {
	int idx;
	idx = _phi[abs(k) % 16];
	idx = _phi[abs(j + idx) % 16];
	idx = _phi[abs(i + idx) % 16];
	return idx;
}

int SolidNoise::intGamma(int i, int j) const {
	int idx;
	idx = _phi[abs(j) % 16];
	idx = _phi[abs(i + idx) % 16];
	return idx;
}

float SolidNoise::knot(int i, int j, int k, Vector3 &v) const {
	return (omega(v[0]) * omega(v[1]) * omega(v[2]) * dot_product(gamma(i, j, k), v));
}
