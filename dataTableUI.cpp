#pragma once
#include "dataTableUI.h"
#include "settings.h"

#define IM_MIN(A, B)	(((A) < (B)) ? (A) : (B))
#define IM_MAX(A, B)	(((A) >= (B)) ? (A) : (B))

void alignCenter(const char[]);
float getTableHeight(float, int);

void RenderDataTable()
{
	static ImGuiTableFlags table_flags = ImGuiTableFlags_Borders | ImGuiTableFlags_ScrollY | ImGuiTableFlags_RowBg;
	static ImVec2 CellPadding(5.0f, 5.0f);
	const float TEXT_BASE_HEIGHT = ImGui::GetTextLineHeightWithSpacing();
	const int rowsCount = Global::customerCount;
	const int columnsCount = 4;
	const int rowsToDisplay = 8;
	const ImU32 bg_color = ImGui::GetColorU32(ImVec4(0.78f, 0.70f, 0.62f, 1.0f)); // fix Hard-coded color
	static ImVec2 outer_size = ImVec2(0.0f, TEXT_BASE_HEIGHT * rowsToDisplay);
	ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, CellPadding);

	if (ImGui::BeginTable("data table", columnsCount, table_flags, ImVec2(0.0f, getTableHeight(TEXT_BASE_HEIGHT, rowsToDisplay))))
	{
		// Table Headers
		ImGui::TableSetupColumn("#", ImGuiTableColumnFlags_WidthFixed, 40.0f);

		ImGui::TableSetupColumn("ZIP Code");
		ImGui::TableSetupColumn("Age");
		ImGui::TableSetupColumn("Items");
		ImGui::TableNextRow(ImGuiTableRowFlags_Headers);
		ImGui::TableSetBgColor(ImGuiTableBgTarget_RowBg0, bg_color);
		for (int column = 0; column < columnsCount; column++)
		{
			ImGui::TableSetColumnIndex(column);
			const char* columnName = ImGui::TableGetColumnName(column);
			alignCenter(columnName);
			ImGui::TableHeader(columnName);
		}

		for (int row = 0; row < rowsCount; row++)
		{
			ImGui::TableNextRow();

			// ID
			ImGui::TableNextColumn();
			alignCenter(row + 1 > 9 ? "##" : "#");
			ImGui::Text("%d", row + 1);

			// ZIP Code
			ImGui::TableNextColumn();
			alignCenter("#####");
			ImGui::Text("%d", Global::customers[row].zipCode);

			// Age
			ImGui::TableNextColumn();
			alignCenter(Global::customers[row].age > 9 ? "##" : "#");
			ImGui::Text("%d", Global::customers[row].age);

			// Items                        
			ImGui::TableNextColumn();
			alignCenter(Global::customers[row].items > 9 ? "##" : "#");
			ImGui::Text("%d", Global::customers[row].items);
		}

		ImGui::EndTable();
	}
	ImGui::PopStyleVar();
}

void alignCenter(const char text[])
{
	float textWidth = ImGui::CalcTextSize(text).x;
	float columnWidth = ImGui::GetContentRegionAvail().x;

	if (columnWidth > textWidth)
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + (columnWidth - textWidth) * 0.5f);
}

float getTableHeight(float baseHeight, int minRows)
{
	return (baseHeight - 7) * IM_MIN(Global::customerCount, minRows) + 30;
}