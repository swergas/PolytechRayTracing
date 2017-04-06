/*
 * ParamSurf.h
 *
 *  Created on: 31 mai 2011
 *      Author: Sandra & Marion
 */

#ifndef PARAMSURF_H_
#define PARAMSURF_H_

#include "Shape.h"
#include "Material.h"
#include "Vector3.h"
#include "Color.h"
#include "Set.h"
#include "Ray.h"
#include <string.h>
#include <itpp/itbase.h>

using namespace itpp;
using namespace std;


class ParamSurf : public Shape {
public:
	Color color;
	mat M0, M1, M2, M3;
	string surface;

	ParamSurf (const Color &_color, mat M0, mat M1, mat M2, mat M3, string surface);
	virtual ~ParamSurf();

	Vector3 normal (const Vector3& pt) const;

	Set<double> intersect ( const Ray& r ) const;
	
	Set<mat> make_pencil (const Ray& r) const;

	Set<mat> make_reduction(mat A, mat B) const;

	Vector3 normalButterfly(double s, double t) const;

	Vector3 normalSteiner(double s, double t) const;

};

#endif /* PARAMSURF_H_ */
