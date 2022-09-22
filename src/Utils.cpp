#include "Utils.h"

namespace Utils {
	void DrawCenteredText(const char* text, Vector2 pos, int fontSize, Color color) {
		int textWide = MeasureText(text, fontSize);
		DrawText(text, (pos.x) - (textWide * .5), (pos.y) - (fontSize * .5), fontSize, color);
	}

	float Modulo(Vector2 vec) {
		return sqrtf((vec.x * vec.x) + (vec.y * vec.y));
	}

	float RadiansToDegrees(float rad) {
		return (rad * (180.0 / m_pi));
	}

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
		targetAng = RadiansToDegrees(targetAng);
		return targetAng;
	}
}