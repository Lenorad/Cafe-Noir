#include "dataTable.h"
#include "settings.h"

inline float tableAvailRegY = 0;

void Load_dataTable()
{
	tableAvailRegY = ImGui::GetContentRegionAvail().y;

	ImGui::SetWindowFontScale(1.35f);
	ImGui::PushFont(Global::gBoldFont);
	ImGui::Text("Data Table");
	ImGui::PopFont();

	RenderDataTable();
}
