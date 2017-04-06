#ifndef CYLINDRE_H_
#define CYLINDRE_H_

#include "Shape.h"
#include "Matrix3.h"
#include <cmath>

class Cylindre : public Shape {
public:
	double _rayon;
	Matrix3 _rotation;
	Vector3 _translation;

	Cylindre(const Color& color, const Material& material,
			const Vector3& origin, const Vector3& height, double rayon = 1);
	virtual ~Cylindre();

	void init(const Vector3& origin, const Vector3& height);

	virtual Vector3 normal(const Vector3 &ptIntersect) const;
	virtual Set<double> ensIntersect(const Ray &rayon) const;
	virtual bool belongsTo(const Vector3& ptIntersect) const;
};

#endif /* CYLINDRE_H_ */
