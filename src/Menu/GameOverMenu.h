#pragma once

namespace GameOver {
	enum class Options {
		PLAYAGAIN,
		RETURNTOMENU,
		COUNT
	};

	void Update();
	void AdjustToRes();
	void Init();
}
