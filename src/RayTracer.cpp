#include "RayTracer.h"
#include <iostream>

RayTracer::RayTracer(Scene &scene, PhongModel &lightModel, ScreenV2 &camera) :
	_scene(scene), _lightModel(lightModel), _camera(camera) {
	NB_OF_INTERATIONS = 5;

	for (int i = 0; i < _scene._shapes->length(); i++) {
		Color c = _scene._shapes->get(i)->_color;
	}
}

RayTracer::~RayTracer() {
}

/**
 *  - Iterate over all the pixels of the screen
 *	- calculate colors with calculateColor
 */
void RayTracer::raytrace(Image* img) {

	//Width and height of the image
	int width = img->_width;
	int height = img->_height;

	//Iterate over all the pixels of the screen/image
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			//Create the ray from the observer point, passing through the pixel
			Ray r = Ray(_camera._observer, _camera.getPixel(x, y) - _camera._observer);

			//Set the pixel accoring to the calculated Color/Light
			img->setPixel(x, y, calculateColor(r, NB_OF_INTERATIONS));
		}

	}
}

/**
 *  raytrace with antialiasing
 *
 */
void RayTracer::raytrace(Image* img, int size) {
	cout << "\nCreating picture..." << endl;

	if (size < 2) {
		raytrace(img);
	} else {
		//Width and height of the image
		int width = img->_width;
		int height = img->_height;

		//Iterate over all the pixels of the screen/image
		for (int y = 0; y < height; ++y) {
			for (int x = 0; x < width; ++x) {
				Color c = Color(0, 0, 0);
				for (double dx = -0.45; dx <= 0.45; dx += 0.9 / (size - 1)) {
					for (double dy = -0.45; dy <= 0.45; dy += 0.9 / (size - 1)) {
						//Create the ray from the observer point, passing through the pixel
						Ray r = Ray(_camera._observer, _camera.getPixel(x + dx, y + dy) - _camera._observer);
						c += calculateColor(r, NB_OF_INTERATIONS);
					}
				}
				//Set the pixel accoring to the calculated Color/Light
				img->setPixel(x, y, c / pow(size, 2));
			}
		}
	}
	cout << "Done" << endl;
}

/**
 * Implementation of algorithm given on P65 of the Script
 * (With the discussed modifications)
 */
Color RayTracer::calculateColor(Ray &r, int recursions) {

	//FIXME Initialize with the background color
	Color c = Color(0.0, 0.0, 0.0);

	//Get the first intersection with any shape
	Shape* closestShape = _scene._shapes->get(0);
	double closestIP;
	bool hasIntersection = false;
	r[1].normalize();
	Ray r_moved = Ray(r.getPoint(1), r.getDirection());
	for (int i = 0; i < _scene._shapes->length(); i++) {
		Set<double> intersections = _scene._shapes->get(i)->ensIntersect(r_moved);

		if (!hasIntersection && !intersections.empty()) {
			closestShape = _scene._shapes->get(i);
			closestIP = intersections[0];
			hasIntersection = true;
		} else if (hasIntersection && !intersections.empty()
				&& intersections[0] < closestIP) {
			closestShape = _scene._shapes->get(i);
			closestIP = intersections[0];
		}

	}

	//if there are any intersections
	if (hasIntersection) {
		//Get the Point of the first intersection
		Vector3 intersection = r_moved.getPoint(closestIP); //P := intersection

		//The normal at the point of intersection
		Vector3 n = closestShape->normal(intersection).normalize();

		//Make sure the normal points into the right direction
		//FIXME is this correct??
		Vector3 r_dir_op = -r.getDirection();
		if (dot_product(r_dir_op, n) < 0) {
			//if (dot_product(V, n) < 0) {
			n = -n;
		}
		Ray normal = Ray(intersection, n);

		//The reflected ray at the point of intersection
		//FIXME Move to the shape class, as it is the same for all the shapes
		Ray reflected = Ray(intersection, (2 * n * (dot_product(n, r_dir_op)) - r_dir_op));

		/*
		 * Calculate the light compartments using the lightmodel
		 */

		//Ambient color
		//FIXME: Take L_a of scene instead of 1
		c = 1 * _lightModel.getAmbient(closestShape->_material)
				* closestShape->getColor(intersection);

		for (int i = 0; i < _scene._lightSources->length(); i++) {
			LightSource* l = _scene._lightSources->get(i);
			if (!isHidden(l, intersection)) {

				double diffuse = _lightModel.getDiffuse(normal, l,
						closestShape->_material);
				double specular = _lightModel.getSpecular(reflected, l,
						closestShape->_material);
				c += diffuse * closestShape->getColor(intersection)
						* l->_intensity;
				c += specular * l->_color * l->_intensity;

			}
		}

		//Recursive call
		if (recursions > 0) {
			c += closestShape->_material.k_reflex * calculateColor(reflected, --recursions);
		}
	}
	return c;
}

/**
 * Implement Algorithm to test, weather there are objects between a point
 * and our light sources
 */
bool RayTracer::isHidden(LightSource* lightSource, Vector3 &point) {
	//Create the ray between intersection point and light source
	Ray ray = Ray(point, (lightSource->_position - point).normalize());
	Vector3 point_moved = point + 0.01 * ray[1];
	ray[0] = point_moved;
	//Get the first intersection with any shape
	Shape* closestShape = _scene._shapes->get(0);
	double closestIP;
	bool hasIntersection = false;

	for (int i = 0; i < _scene._shapes->length(); i++) {
		Set<double> intersections = _scene._shapes->get(i)->ensIntersect(ray);

		if (!hasIntersection && !intersections.empty()) {
			closestShape = _scene._shapes->get(i);
			closestIP = intersections[0];
			hasIntersection = true;
		} else if (hasIntersection && !intersections.empty()
				&& intersections[0] < closestIP) {
			closestShape = _scene._shapes->get(i);
			closestIP = intersections[0];
			hasIntersection = true;
		}
		if (hasIntersection) {
			Vector3 intersection = ray.getPoint(closestIP);
			//Create a vector between the two object intersections
			Vector3 point_intersection = intersection - point_moved;
			//Create a vector between object intersection and light source
			Vector3 point_light = lightSource->_position - point_moved;
			//If |point_light| > |point_intersection| there is shadow
			if (point_light.norm() > point_intersection.norm())
				return true;
		}
	}

	return false;
}
