#include <scene.hpp>

void Scene::AddObject(GraphicObject object)
{
	this->objectList.push_back(object);
}