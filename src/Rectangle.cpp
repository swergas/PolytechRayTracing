#include "Rectangle.h"
#include <cmath>
#include <iostream>

Rectangle::Rectangle(const Color &color, const Material &material, const Ray &normAndPoint, double height, double width) :
	Plane(color, material, normAndPoint), _height(height), _width(width) {
}

Rectangle::~Rectangle() {
}

Set<double> Rectangle::ensIntersect(const Ray &rayon) const {
	Set<double> res = Set<double>(1);
	double t = (
		_d - _normAndPoint[1][0]*rayon[0][0] - _normAndPoint[1][1]*rayon[0][1] - _normAndPoint[1][2]*rayon[0][2])
		/(_normAndPoint[1][0]*rayon[1][0] + _normAndPoint[1][1]*rayon[1][1] + _normAndPoint[1][2]*rayon[1][2]
	);

	Vector3 inter = rayon.getPoint(t);
	if ((fabs(inter[0]-_normAndPoint[0][0]) < _width/2.0
		&& fabs(inter[2]-_normAndPoint[0][2]) < _height/2.0)
		&& t > 0) {
		res.add(t);
	}

	return res;
}
