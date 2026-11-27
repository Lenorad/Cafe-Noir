#include "records.h"

void Load_recordsPage()
{
    ImGui::BeginChild(
        "Records",
        ImVec2(0, 0),
        true
    );
    ImGui::Text("This is Records Page");
    ImGui::SameLine();
    ImGui::TextDisabled("(underdevelopment)");
    ImGui::EndChild();
}