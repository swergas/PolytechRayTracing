#ifndef SHAPE_H_
#define SHAPE_H_

#include "Vector3.h"
#include "Color.h"
#include "Ray.h"
#include "Set.h"
#include "Material.h"

class Shape {
public:
	Color _color;
	Material _material;

	Shape();
	virtual ~Shape();

	virtual Vector3 normal(const Vector3 &ptIntersect) const = 0;
	virtual Set<double> ensIntersect(const Ray &rayon) const = 0;
	virtual Color getColor(const Vector3 &ptIntersect);
	virtual bool belongsTo(const Vector3 &ptIntersect) const = 0;
};

#endif /* SHAPE_H_ */
