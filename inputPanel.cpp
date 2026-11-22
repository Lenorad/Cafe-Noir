#pragma once
#include "inputPanel.h"
#include "settings.h"

bool Load_inputPanel()
{
	ImGui::Spacing();

	ImGui::SetWindowFontScale(1.35f);
	ImGui::PushFont(Global::gBoldFont);
	ImGui::Text("Welcome to Cafe Noir!");
	ImGui::PopFont();
	ImGui::SetWindowFontScale(1.0f);

	ImGui::PushFont(Global::gBoldFont);
	ImGui::Text("Customer Management Dashboard");
	ImGui::PopFont();

	ImGui::Separator();
	ImGui::Spacing();

	ImGui::SetWindowFontScale(1.15f);

	ImGui::Text("Total Customers:");
	ImGui::SameLine(0.0f, 4.0f);
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 2.0f);

	if (Global::numFont) ImGui::PushFont(Global::numFont);
		ImGui::Text("%d", Global::customerCount);
	if (Global::numFont) ImGui::PopFont();
		ImGui::SetWindowFontScale(1.0f);

	ImGui::Spacing();
	RenderCustomerInput(Global::customers, Global::customerCount);
	return true;
}