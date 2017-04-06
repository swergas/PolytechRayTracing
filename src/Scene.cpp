#include "Scene.h"

Scene::Scene(Set<Shape*> *shapes, Set<LightSource*> *lightSources) :
	_lightSources(lightSources), _shapes(shapes) {
}

Scene::~Scene() {
}
