#pragma once

#include <vector>
#include <mesh.hpp>

class Scene
{
public:
	std::vector<Mesh*> meshList;

	void AddMesh(Mesh* mesh);
};