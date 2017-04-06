#ifndef RAYTRACER_H_
#define RAYTRACER_H_

#include <iostream>
#include <fstream> // ofstream
#include "Vector3.h"
#include "ScreenV2.h"
#include "Sphere.h"
#include "Ray.h"
#include "Image.h"
#include "Scene.h"
#include "ScreenV2.h"
#include "LightSource.h"
#include "PhongModel.h"
#include "Color.h"

const double PI = 3.141592;

class RayTracer {
public:
	Scene _scene;
	PhongModel _lightModel;
	ScreenV2 _camera;

	RayTracer(Scene &scene, PhongModel &lightModel, ScreenV2 &camera);
	virtual ~RayTracer();
	virtual void raytrace(Image* img);
	virtual void raytrace(Image* img, int size);

private:
	int NB_OF_INTERATIONS;

	virtual Color calculateColor(Ray &r, int recursions);
	virtual bool isHidden(LightSource* lightSource, Vector3 &point);
};

#endif /* RAYTRACER_H_ */
