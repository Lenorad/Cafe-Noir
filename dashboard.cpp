#include "dashboard.h"

void Load_dashboardPage()
{
    ImGui::BeginChild(
        "MainContent",
        ImVec2(0, 0),
        true
    );
    
    ImGui::Spacing();
    
    static ImGuiTableFlags column_layout = ImGuiTableFlags_BordersInnerV;
    if (ImGui::BeginTable("Double Column Layout", 2, column_layout))
    {
        ImGui::TableSetupColumn("first column", ImGuiTableColumnFlags_WidthFixed, ImGui::GetContentRegionAvail().x * 0.33f);
        ImGui::TableNextRow();
        
        ImGui::TableSetColumnIndex(0);
        Load_inputPanel();

        ImGui::TableSetColumnIndex(1);
        Load_dataTable();
        //Load_barchart();

        ImGui::EndTable();
    }
    ImGui::EndChild();
}