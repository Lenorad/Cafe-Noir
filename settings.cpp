#include "settings.h"
#include "csvIO.h"

namespace Global {
	ImFont* gBoldFont = nullptr;
	ImFont* numFont = nullptr;
	int customerCount = 0;
	Pages currentPage = Pages::Dashboard;
	Customer customers[MAX_CUSTOMERS] = {};
}

namespace Settings {
	void SetupCoffeeTheme()
	{
		ImGuiStyle& style = ImGui::GetStyle();

		// Rounded corners 
		style.WindowRounding = 12.0f;
		style.ChildRounding = 12.0f;
		style.FrameRounding = 8.0f;
		style.GrabRounding = 8.0f;
		style.PopupRounding = 8.0f;
		style.ScrollbarRounding = 8.0f;

		// Spacing
		style.WindowPadding = ImVec2(16, 16);
		style.FramePadding = ImVec2(12, 8);
		style.ItemSpacing = ImVec2(10, 10);

		// Borders
		style.WindowBorderSize = 0.0f;
		style.ChildBorderSize = 1.0f;
		style.FrameBorderSize = 0.0f;

		ImVec4* colors = style.Colors;

		// Dark coffee background
		colors[ImGuiCol_WindowBg] =
			ImVec4(0.33f, 0.16f, 0.05f, 1.0f);

		// Table header
		colors[ImGuiTableBgTarget_CellBg] =
			ImVec4(0.88f, 0.78f, 0.70f, 0.7f);

		// Cream panels
		colors[ImGuiCol_ChildBg] =
			ImVec4(0.95f, 0.87f, 0.75f, 1.0f);

		// Text
		colors[ImGuiCol_Text] =
			ImVec4(0.20f, 0.13f, 0.09f, 1.0f);

		// Input fields
		colors[ImGuiCol_FrameBg] =
			ImVec4(1.0f, 0.97f, 0.92f, 1.0f);

		colors[ImGuiCol_FrameBgHovered] =
			ImVec4(0.96f, 0.90f, 0.81f, 1.0f);

		colors[ImGuiCol_FrameBgActive] =
			ImVec4(1.0f, 0.94f, 0.84f, 1.0f);

		// Buttons 
		colors[ImGuiCol_Button] =
			ImVec4(0.43f, 0.21f, 0.07f, 1.0f);

		colors[ImGuiCol_ButtonHovered] =
			ImVec4(0.52f, 0.29f, 0.12f, 1.0f);

		colors[ImGuiCol_ButtonActive] =
			ImVec4(0.38f, 0.18f, 0.06f, 1.0f);

		// Borders and separators
		colors[ImGuiCol_Border] =
			ImVec4(0.72f, 0.55f, 0.37f, 0.8f);

		colors[ImGuiCol_Separator] =
			ImVec4(0.72f, 0.55f, 0.37f, 0.8f);

		// Title bar colors
		colors[ImGuiCol_TitleBg] =
			ImVec4(0.17f, 0.075f, 0.035f, 1.0f);

		colors[ImGuiCol_TitleBgActive] =
			ImVec4(0.17f, 0.075f, 0.035f, 1.0f);

		// Scrollbar
		colors[ImGuiCol_ScrollbarBg] =
			ImVec4(0.85f, 0.75f, 0.62f, 1.0f);

		colors[ImGuiCol_ScrollbarGrab] =
			ImVec4(0.55f, 0.35f, 0.22f, 1.0f);
	}

	bool Load_fonts()
	{
		return true;
	}

	bool Load_csv()
	{
		if (openFile())
		{
			Global::customerCount = getNumOfCustomer();
			for (int i = 0; i < Global::customerCount; i++)
			{
				Customer customer;
				customer = readData(i);
				Global::customers[i] = customer;
			}
			closeFile();
			return true;
		}
		else
		{
			return false;
		}
	}
}

void Load_settingsPage()
{
	ImGui::BeginChild(
		"Settings",
		ImVec2(0, 0),
		true
	);
	ImGui::Text("This is Settings Page");
	ImGui::SameLine();
	ImGui::TextDisabled("(underdevelopment)");
	ImGui::EndChild();
}