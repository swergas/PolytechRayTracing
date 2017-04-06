#include "Cylindre.h"

Cylindre::Cylindre(const Color& color, const Material& material, const Vector3& origin,
		const Vector3& height, double rayon) {
	this->_color = color;
	this->_material = material;
	_rayon = rayon;
	init(origin, height);
}

Cylindre::~Cylindre() {
}

void Cylindre::init(const Vector3& origin, const Vector3& height) {
	Vector3 ox = (height - origin).normalize();
	Vector3 oy;
	if (ox[0] != 0 || ox[1] != 0) {
		oy = (Vector3(-ox[1], ox[0], 0)).normalize();
	} else {
		oy = (Vector3(1, 0, 0));
	}
	Vector3 oz = cross_product(ox, oy);

	_rotation = Matrix3(ox, oy, oz);
	_translation = -origin;
}

Vector3 Cylindre::normal(const Vector3 &ptIntersect) const {
	return _rotation * Vector3(ptIntersect[0], ptIntersect[1], 0);
}

Set<double> Cylindre::ensIntersect(const Ray &rayon) const {
	Set<double> res;

	double ox = rayon[0][0];
	double oy = rayon[0][1];
	double oz = rayon[0][2];
	double dx = rayon[1][0];
	double dy = rayon[1][1];
	double dz = rayon[1][2];

	double _a = _rotation(0, 0)*_rotation(0, 0) + _rotation(0, 1)*_rotation(0, 1);
	double _b = _rotation(1, 0)*_rotation(1, 0) + _rotation(1, 1)*_rotation(1, 1);
	double _c = _rotation(2, 0)*_rotation(2, 0) + _rotation(2, 1)*_rotation(2, 1);
	double _d = 2*(_rotation(0, 0)*_rotation(1, 0) + _rotation(0, 1)*_rotation(1, 1));
	double _e = 2*(_rotation(0, 0)*_rotation(2, 0) + _rotation(0, 1)*_rotation(2, 1));
	double _f = 2*(_rotation(1, 0)*_rotation(2, 0) + _rotation(1, 1)*_rotation(2, 1));
	double _g = 2*(_rotation(0, 0)*_translation[0] + _rotation(0, 1)*_translation[1]);
	double _h = 2*(_rotation(1, 0)*_translation[0] + _rotation(1, 1)*_translation[1]);
	double _i = 2*(_rotation(2, 0)*_translation[0] + _rotation(2, 0)*_translation[1]);
	double _j = _translation[0]*_translation[0] + _translation[1]*_translation[1] -(_rayon * _rayon);


	double alpha = _a*dx*dx + _b*dy*dy + _c*dz*dz
				 + 2*_d*dx*dy + 2*_e*dx*dz + 2*_f*dy*dz;

	double beta  = 2*_a*ox*dx + 2*_b*oy*dy + 2*_c*oz*dz
				 + 2*_d*(ox*dy + oy*dx) + 2*_e*(ox*dz + oz*dx) + 2*_f*(oy*dz + oz*dy)
				+ _g*dx + _h*dy + _i*dz;

	double gamma = _a*ox*ox + _b*oy*oy + _c*oz*oz
				 + 2*_d*ox*oy + 2*_e*ox*oz + 2*_f*oy*oz
				 + _g*ox + _h*oy + _i* oz
				 + _j;

	double delta = beta * beta - 4 * alpha * gamma;

	delta = sqrt(delta);
	if (delta == 0) {
		res.add(-beta / (2 * alpha));
	} else if (delta > 0) {
		res.add((-beta - delta) / (2 * alpha));
		res.add((-beta + delta) / (2 * alpha));
	}

	return res;
}

bool Cylindre::belongsTo(const Vector3& ptIntersect) const {
	return false;
}
