#pragma once

#include <vector>
#include <vector.hpp>
#include <object.hpp>
#include <math.h>

namespace MovementUtility
{
    Vector3 Bezier(std::vector<Vector3> controlPoints, float t);
};

namespace CollisionUtility
{
    bool SpherePoint(GraphicObject obj, Vector3 point);
    bool RectanglePoint(GraphicObject obj, Vector3 point);
    bool RectangleRectangle(GraphicObject obj1, GraphicObject obj2);
};

namespace Utility
{
	glm::mat4 MakeCorrectGlmMatrix(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33
	);

	void CalculateGlobalBoundingBox(GraphicObject obj, Vector3* bbox_min, Vector3* bbox_max);
}