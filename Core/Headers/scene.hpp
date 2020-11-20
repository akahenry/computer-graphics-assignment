#pragma once

#include <vector>
#include <object.hpp>
#include <light.hpp>

class Scene
{
public:
	std::vector<GraphicObject*> objectList;
	std::vector<LightSource*> lightList;

	/**
	 * Push an object to the scene
	 * 
	 * @param[in] object an GraphicObject to be added in the scene
	 */
	void AddObject(GraphicObject* object);

	/**
	 * Push an light source to the scene
	 * 
	 * @param[in] light an LightSource to be added in the scene
	 */
	void AddLight(LightSource* light);
};