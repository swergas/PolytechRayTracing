#ifndef SCENE_H_
#define SCENE_H_

#include "LightSource.h"
#include "Shape.h"
#include "Set.h"
#include "Color.h"

class Scene {
public:
	Set<LightSource*> *_lightSources;
	Set<Shape*> *_shapes;
	Color L_a;

	Scene(Set<Shape*> *shapes, Set<LightSource*> *lightSources);
	virtual ~Scene();
};

#endif /* SCENE_H_ */
