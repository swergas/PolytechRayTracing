#include "Plane.h"
#include <cmath>

Plane::Plane(const Color &color, const Material &material, const Ray &normAndPoint) :
	_normAndPoint(normAndPoint) {
	this->_color = color;
	this->_material = material;
	//Calculate the d constant in the plane equation P:ax+by+cz=d
	_d = _normAndPoint[0][0] * _normAndPoint[1][0]
	   + _normAndPoint[0][1] * _normAndPoint[1][1]
	   + _normAndPoint[0][2] * _normAndPoint[1][2];
}

Plane::~Plane() {
}

Set<double> Plane::ensIntersect(const Ray &rayon) const {
	Set<double> res = Set<double>(1);
	double t = (
		_d - _normAndPoint[1][0]*rayon[0][0] - _normAndPoint[1][1]*rayon[0][1] - _normAndPoint[1][2]*rayon[0][2])
		/(_normAndPoint[1][0]*rayon[1][0] + _normAndPoint[1][1]*rayon[1][1] + _normAndPoint[1][2]*rayon[1][2]
	);

	if (t > 0) {
		res.add(t);
	}

	return res;
}

Vector3 Plane::normal(const Vector3 &ptIntersect) const {
	return _normAndPoint[1];
}

bool Plane::belongsTo(const Vector3 &ptIntersect) const {
	return abs(_d + ptIntersect[0] * _normAndPoint[1][0]
	              + ptIntersect[1] * _normAndPoint[1][1]
	              + ptIntersect[2] * _normAndPoint[1][2]) < 0.001;
}
