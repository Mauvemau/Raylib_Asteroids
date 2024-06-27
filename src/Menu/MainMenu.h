#pragma once

namespace MainMenu {
	enum class Options {
		PLAY,
#ifdef _WIN32
		SETTINGS,
#endif // _WIN32
		CREDITS,
		EXIT,
		COUNT
	};

	void Update();
	void AdjustToRes();
	void Init();
}
