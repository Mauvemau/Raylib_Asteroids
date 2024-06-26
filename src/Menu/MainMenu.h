#pragma once

namespace MainMenu {
	enum class Options {
		PLAY,
		SETTINGS,
		CREDITS,
		EXIT,
		COUNT
	};

	void Update();
	void AdjustToRes();
	void Init();
}
