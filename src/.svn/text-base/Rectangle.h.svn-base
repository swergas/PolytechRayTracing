#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include "Plane.h"

class Rectangle : public Plane {
public:
	double _height;
	double _width;

	Rectangle(const Color &color, const Material &material, const Ray &normAndPoint, double height, double width);
	virtual ~Rectangle();

	virtual Set<double> ensIntersect(const Ray &rayon) const;
};

#endif /* RECTANGLE_H_ */
