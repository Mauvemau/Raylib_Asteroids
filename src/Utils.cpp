#include "Utils.h"

namespace Utils {
	Vector2 GetTargetVector(Vector2 origin, Vector2 target) {
		Vector2 targetVector = {
			(target.x - origin.x),
			(target.y - origin.y)
		};
		return targetVector;
	}

	float GetDistance(Vector2 v1, Vector2 v2)
	{
		float distX = v1.x - v2.x;
		float distY = v1.y - v2.y;
		return sqrt((distX * distX) + (distY * distY));
	}

	float CalculateRotationAngle(Vector2 origin, Vector2 target) {
		Vector2 targetVector = GetTargetVector(origin, target);

		float targetAng = atan2(targetVector.x, -targetVector.y);
		targetAng = targetAng * (180.0 / M_PI);
		return targetAng;
	}
}