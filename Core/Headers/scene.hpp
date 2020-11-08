#pragma once

#include <vector>
#include <object.hpp>

class Scene
{
public:
	std::vector<GraphicObject> objectList;

	void AddObject(GraphicObject object);
};