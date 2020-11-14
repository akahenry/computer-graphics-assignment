#pragma once

#include <vector>
#include <object.hpp>
#include <light.hpp>

class Scene
{
public:
	std::vector<GraphicObject*> objectList;
	std::vector<LightSource*> lightList;

	void AddObject(GraphicObject* object);
	void AddLight(LightSource* light);
};