#ifndef QUADRICS_H_
#define QUADRICS_H_

#include "Shape.h"
#include <cmath>

class Quadrics: public Shape {
public:
	double _a, _b, _c, _d, _e, _f, _g, _h, _i, _j;

	Quadrics(const Color &color, const Material &material, double a, double b, double c, double d, double e, double f,
			double g, double h, double i, double j);
	virtual ~Quadrics();

	virtual Vector3 normal(const Vector3 &ptIntersect) const;
	virtual Set<double> ensIntersect(const Ray &rayon) const;
	virtual bool belongsTo(const Vector3& ptIntersect) const;
};

#endif /* QUADRICS_H_ */
