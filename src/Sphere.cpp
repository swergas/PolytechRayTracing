#include "Sphere.h"
#include <cmath>

Sphere::Sphere(const Color &color, const Material &material, const Vector3 &center, double radius) :
	_center(center), _radius(radius) {
	this->_color = color;
	this->_material = material;
}

Sphere::~Sphere() {
}

Vector3 Sphere::normal(const Vector3 &ptIntersect) const {
	return (ptIntersect - _center);
}

Set<double> Sphere::ensIntersect(const Ray &rayon) const {
	Set<double> s = Set<double> (2);
	Vector3 d_o_x = dot_product(rayon.getDirection(), (rayon.getOrigin() - _center));
	Vector3 o_c = dot_product(rayon.getOrigin(), _center);

	double a = rayon.getDirection().norm() * rayon.getDirection().norm();
	double b = 2 * (d_o_x[0] + d_o_x[1] + d_o_x[2]);
	double c = pow(_center.norm(), 2) + pow(rayon.getOrigin().norm(), 2) - 2 * (o_c[0] + o_c[1] + o_c[2]) - _radius * _radius;

	//Apply solve function (-b +- sqrt(b^2-4ac))/2a
	double d = b * b - 4 * a * c; //the term in the root

	if (d > 0) { //We have an intersection
		double t1 = (-b - sqrt(d)) / (2 * a);
		double t2 = (-b + sqrt(d)) / (2 * a);
		if (t1 < t2) {
			if (t1 > 0) {
				s.add(t1);
				s.add(t2);
			}
		} else if (t2 > 0) {
			s.add(t2);
		}
	}
	return s;
}

bool Sphere::belongsTo(const Vector3 &ptIntersect) const {
	return fabs(sqrt((ptIntersect[0] - _center[0])*(ptIntersect[0] - _center[0])
				   + (ptIntersect[1] - _center[1])*(ptIntersect[1] - _center[1])
				   + (ptIntersect[2] - _center[2])*(ptIntersect[2] - _center[2])) - _radius) < 0.001;
}
