#include <utils.hpp>


Vector3 MovementUtility::Bezier(std::vector<Vector3> controlPoints, float t)
{
    Vector3 result(0, 0, 0);
    int n = controlPoints.size() - 1;
    t -= floor(t);

    for (int i = 0; i < controlPoints.size(); i++)
    {
        result += controlPoints[i] * float(tgamma(n + 1) / (tgamma(i + 1) * tgamma(n - i + 1)) * pow(1 - t, n - i) * pow(t, i));
    }

    return result;
}

Vector3 MovementUtility::FlagPosition(GraphicObject road, int number)
{
	Vector3 global_bbox_min;
	Vector3 global_bbox_max;
	
	Utility::CalculateGlobalBoundingBox(road, &global_bbox_min, &global_bbox_max);

	std::vector<Vector3> points = { global_bbox_min * 0.8, Vector3(global_bbox_min.x, global_bbox_min.y, global_bbox_max.z) * 0.8, global_bbox_max * 0.8, Vector3(global_bbox_max.x, global_bbox_max.y, global_bbox_min.z) * 0.8, global_bbox_min * 0.8 };

	return points[number%4];
}

bool CollisionUtility::SpherePoint(GraphicObject obj, Vector3 point)
{
	Vector3 global_bbox_min;
	Vector3 global_bbox_max;
	Vector3 global_origin;

	Utility::CalculateGlobalBoundingBox(obj, &global_bbox_min, &global_bbox_max);

	global_origin = (global_bbox_max + global_bbox_min) / 2;

	float radius_min = (global_bbox_min - global_origin).Norm();
	float radius_max = (global_bbox_max - global_origin).Norm();

	float radius = radius_min >= radius_max ? radius_min : radius_max;

	return (point - global_origin).Norm() <= radius;
}

bool CollisionUtility::RectanglePoint(GraphicObject obj, Vector3 point)
{
	Vector3 global_bbox_min;
	Vector3 global_bbox_max;
	Vector3 global_origin;

	Utility::CalculateGlobalBoundingBox(obj, &global_bbox_min, &global_bbox_max);

	global_origin = (global_bbox_max + global_bbox_min) / 2;

	return (point.x >= global_bbox_min.x && point.x <= global_bbox_max.x) &&
		(point.y >= global_bbox_min.y && point.y <= global_bbox_max.y) &&
		(point.z >= global_bbox_min.z && point.z <= global_bbox_max.z);
}

bool CollisionUtility::RectangleRectangle(GraphicObject obj1, GraphicObject obj2)
{
	Vector3 global_bbox_min;
	Vector3 global_bbox_max;
	Vector3 global_origin;

	Utility::CalculateGlobalBoundingBox(obj1, &global_bbox_min, &global_bbox_max);

	global_origin = (global_bbox_max + global_bbox_min) / 2;

	return CollisionUtility::RectanglePoint(obj2, global_bbox_min) || 
		CollisionUtility::RectanglePoint(obj2, global_bbox_max) || 
		CollisionUtility::RectanglePoint(obj2, global_origin);
}

void Utility::CalculateGlobalBoundingBox(GraphicObject obj, Vector3* bbox_min, Vector3* bbox_max)
{
	glm::mat4 S = Utility::MakeCorrectGlmMatrix(
		obj.scale.x, 0.0f, 0.0f, 0.0f,
		0.0f, obj.scale.y, 0.0f, 0.0f,
		0.0f, 0.0f, obj.scale.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	float c = cos(obj.rotationAngle);
	float s = sin(obj.rotationAngle);

	Vector3 v = obj.rotationAxis.Normalized();

	float vx = v.x;
	float vy = v.y;
	float vz = v.z;

	// rota��o em torno de um eixo arbitr�rio
	glm::mat4 R = Utility::MakeCorrectGlmMatrix(
		vx * vx * (1 - c) + c, vx * vy * (1 - c) - vz * s, vx * vz * (1 - c) + vy * s, 0.0f,
		vx * vy * (1 - c) + vz * s, vy * vy * (1 - c) + c, vy * vz * (1 - c) - vx * s, 0.0f,
		vx * vz * (1 - c) - vy * s, vy * vz * (1 - c) + vx * s, vz * vz * (1 - c) + c, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	glm::mat4 T = Utility::MakeCorrectGlmMatrix(
		1.0f, 0.0f, 0.0f, obj.position.x,
		0.0f, 1.0f, 0.0f, obj.position.y,
		0.0f, 0.0f, 1.0f, obj.position.z,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	glm::mat4 O = Utility::MakeCorrectGlmMatrix(
		1.0f, 0.0f, 0.0f, obj.origin.x,
		0.0f, 1.0f, 0.0f, obj.origin.y,
		0.0f, 0.0f, 1.0f, obj.origin.z,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	glm::mat4 modelMatrix = T * R * O * S;

	glm::vec4 glm_global_bbox_min = modelMatrix * glm::vec4(obj.mesh->bbox_min.x, obj.mesh->bbox_min.y, obj.mesh->bbox_min.z, 1.0f);
	glm::vec4 glm_global_bbox_max = modelMatrix * glm::vec4(obj.mesh->bbox_max.x, obj.mesh->bbox_max.y, obj.mesh->bbox_max.z, 1.0f);

	bbox_max->x = glm_global_bbox_max.x;
	bbox_max->y = glm_global_bbox_max.y;
	bbox_max->z = glm_global_bbox_max.z;
	bbox_min->x = glm_global_bbox_min.x;
	bbox_min->y = glm_global_bbox_min.y;
	bbox_min->z = glm_global_bbox_min.z;
}

glm::mat4 Utility::MakeCorrectGlmMatrix(
	float m00, float m01, float m02, float m03,
	float m10, float m11, float m12, float m13,
	float m20, float m21, float m22, float m23,
	float m30, float m31, float m32, float m33
)
{
	return glm::mat4(
		m00, m10, m20, m30,
		m01, m11, m21, m31,
		m02, m12, m22, m32,
		m03, m13, m23, m33
	);
}