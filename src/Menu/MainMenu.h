#pragma once

namespace MainMenu {
	enum class Options {
		PLAY,
		CREDITS,
		EXIT,
		COUNT
	};

	void Update();
	void AdjustToRes();
	void Init();
}
