#include "dataTable.h"
#include "settings.h"

void Load_dataTable()
{
	ImGui::SetWindowFontScale(1.35f);
	ImGui::PushFont(Global::gBoldFont);
	ImGui::Text("Input Panel");
	ImGui::PopFont();

	RenderDataTable();
}
