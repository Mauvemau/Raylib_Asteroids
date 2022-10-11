#include "Utils.h"

namespace Utils {
	Vector2 GetRandomSpawnPosition() {
		Vector2 spawnPos = { 0, 0 };
		if (GetRandomValue(0, 1)) {
			spawnPos.x = static_cast<float>(GetRandomValue(0, GetScreenHeight()));
		}
		else {
			spawnPos.y = static_cast<float>(GetRandomValue(0, GetScreenWidth()));
		}
		return spawnPos;
	}

	void DrawCenteredText(const char* text, Vector2 pos, int fontSize, Color color) {
		int textWide = MeasureText(text, fontSize);
		DrawText(text, static_cast<int>((pos.x) - (textWide * .5)), static_cast<int>((pos.y) - (fontSize * .5)), fontSize, color);
	}

	float Modulo(Vector2 vec) {
		return sqrtf((vec.x * vec.x) + (vec.y * vec.y));
	}

	float DegreesToRadians(float deg) {
		return static_cast<float>(deg * (m_pi / 180.0));
	}

	float RadiansToDegrees(float rad) {
		return static_cast<float>(rad * (180.0 / m_pi));
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