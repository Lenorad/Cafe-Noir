#pragma once
#include "imgui.h"
#include "inputPanelUI.h" //  struct Customer

inline const int MAX_CUSTOMERS = 128;

enum class Pages {
	Dashboard,
	Records,
	Analytics,
	Settings
};

void Load_settingsPage();

// =========================
// Global Variables
// =========================
namespace Global {
	extern ImFont* gBoldFont;
	extern ImFont* numFont;
	extern int customerCount;
	extern Pages currentPage;
	extern Customer customers[MAX_CUSTOMERS];
}

namespace Settings {
	void SetupCoffeeTheme();
	bool Load_fonts();
	bool Load_csv();
}