#pragma once


namespace Settings {
	enum class Options {
		RESOLUTION,
		FULLSCREEN,
		RETURNTOMENU,
		COUNT
	};

	enum class Resolutions {
		r640x480,
		r800x600,
		r1024x768,
		r1152x864,
		r1280x720,
		r1280x1024,
		r1360x768,
		r1600x900
	};

	struct Resolution {
		int width;
		int height;
	};

	void Update();
	void InitSettings(); // Inicializa las settings default.
	void AdjustToRes();
	void Init(); // Inicializa el menu
}
