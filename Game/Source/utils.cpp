#include <utils.hpp>

Vector3 MovementUtility::Bezier(std::vector<Vector3> controlPoints, float t)
{
    Vector3 result(0, 0, 0);
    int n = controlPoints.size();
    t -= floor(t);

    for (int i = 0; i < controlPoints.size(); i++)
    {
        result += controlPoints[i] * float(tgamma(n + 1) / (tgamma(i + 1) * tgamma(n - i + 1)) * pow(1 - t, n - i) * pow(t, i));
    }

    return result;
}