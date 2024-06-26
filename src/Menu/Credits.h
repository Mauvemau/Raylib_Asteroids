#pragma once

namespace Credits {
	enum class Options {
		RAYLIB,
		MUSIC,
		ANIMATION,
		SFX,
		SPRITES,
		RETURNTOMENU,
		COUNT
	};

	void Update();
	void AdjustToRes();
	void Init();
}
