#include <scene.hpp>

void Scene::AddObject(GraphicObject* object)
{
	this->objectList.push_back(object);
}

void Scene::AddLight(LightSource* light)
{
	this->lightList.push_back(light);
}