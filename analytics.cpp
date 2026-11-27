#include "analytics.h"

void Load_analyticsPage()
{
    ImGui::BeginChild(
        "Analytics",
        ImVec2(0, 0),
        true
    );
    ImGui::Text("This is Analytics Page");
    ImGui::SameLine();
    ImGui::TextDisabled("(underdevelopment)");
    ImGui::EndChild();
}