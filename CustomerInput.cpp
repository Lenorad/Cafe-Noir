#include "CustomerInput.h"
#include "InputBackend.h"
#include "Data.h"
#include "imgui.h"
#include <string>

extern ImFont* numFont;

void RenderCustomerInput(Customer customers[], int& customerCount)
{
    static int zipCode = 0;
    static int age = 0;
    static int items = 1;

    static std::string message = "";
    static bool hasError = false;
    static bool sessionEnded = false;

    // Customer Information Card
    ImGui::PushStyleVar(
        ImGuiStyleVar_WindowPadding,
        ImVec2(16, 10)
    );

    ImGui::BeginChild(
        "CustomerInputCard",
        ImVec2(0, 0),
        true
    );

    ImGui::SetWindowFontScale(1.35f);

    ImGui::Text("Customer Information");

    ImGui::SetWindowFontScale(1.15f);

    ImGui::Text("Please enter the customer details below.");

    ImGui::Separator();
    ImGui::Dummy(ImVec2(0, 4));

    if (!sessionEnded)
    {
        // ZIP CODE
        ImGui::SetWindowFontScale(1.0f);
        ImGui::Text("ZIP Code");
        ImGui::SetWindowFontScale(1.0f);

        ImGui::PushItemWidth(-1);

        if (numFont) ImGui::PushFont(numFont);

        bool zipEnter = ImGui::InputInt(
            "##ZIP",
            &zipCode,
            0,
            0,
            ImGuiInputTextFlags_EnterReturnsTrue
        );

        if (numFont) ImGui::PopFont();

        ImGui::PopItemWidth();
       
        ImGui::Dummy(ImVec2(0, 4));

        // CUSTOMER AGE
        ImGui::SetWindowFontScale(1.0f);
        ImGui::Text("Customer Age");
        ImGui::SetWindowFontScale(1.0f);

        if (zipEnter)
            ImGui::SetKeyboardFocusHere();

        ImGui::PushItemWidth(-1);

        if (numFont) ImGui::PushFont(numFont);

        bool ageEnter = ImGui::InputInt(
            "##Age",
            &age,
            0,
            0,
            ImGuiInputTextFlags_EnterReturnsTrue
        );

        if (numFont) ImGui::PopFont();

        ImGui::PopItemWidth();
       
        ImGui::Dummy(ImVec2(0, 4));

        // NUMBER OF ITEMS
        ImGui::SetWindowFontScale(1.0f);
        ImGui::Text("Number of Items");
        ImGui::SetWindowFontScale(1.0f);

        if (ageEnter)
            ImGui::SetKeyboardFocusHere();

        ImGui::PushItemWidth(-1);

        if (numFont) ImGui::PushFont(numFont);

        ImGui::InputInt(
            "##Items",
            &items,
            0,
            0,
            ImGuiInputTextFlags_EnterReturnsTrue
        );

        if (numFont) ImGui::PopFont();

        ImGui::PopItemWidth();
        
        ImGui::Dummy(ImVec2(0, 4));

        ImGui::PushStyleColor(
            ImGuiCol_Text,
            ImVec4(1.0f, 1.0f, 1.0f, 1.0f)
        );
        ImGui::SetWindowFontScale(1.2f);

        // SUBMIT BUTTON
        if (ImGui::Button("Submit", ImVec2(130, 42)))
        {
            hasError = false;
            message = "";

            if (zipCode == 0)
            {
                message = "Session ended!";
                sessionEnded = true;
            }
            else if (AddCustomer(
                customers,
                customerCount,
                zipCode,
                age,
                items,
                message))
            {
                customerData newCustomer;

                newCustomer.zipcode = zipCode;
                newCustomer.age = age;
                newCustomer.item = items;

                if (openFile())
                {
                    writeData(newCustomer);
                    closeFile();

                    message = "Customer added successfully.";
                }
                else
                {
                    message = "Error: Could not open data.csv file!";
                    hasError = true;
                }

                zipCode = 0;
                age = 0;
                items = 1;
            }
            else
            {
                hasError = true;
            }
        }
        ImGui::SetWindowFontScale(1.0f);

        ImGui::SameLine();

        // CLEAR BUTTON
        ImGui::SetWindowFontScale(1.2f);

        if (ImGui::Button("Clear", ImVec2(130, 42)))
        {
            zipCode = 0;
            age = 0;
            items = 1;

            message = "";
            hasError = false;
            sessionEnded = false;
        }
        ImGui::SetWindowFontScale(1.0f);

        ImGui::PopStyleColor();
    }
    


    ImGui::Spacing();

    // STATUS MESSAGE
    if (!message.empty())
    {
        ImGui::Spacing();

        if (hasError)
        {
            ImGui::PushStyleColor(
                ImGuiCol_ChildBg,
                ImVec4(1.0f, 0.85f, 0.85f, 1.0f)
            );

            ImGui::BeginChild(
                "ErrorBanner",
                ImVec2(0, 50),
                true
            );
            ImGui::SetWindowFontScale(1.3f);

            ImGui::TextColored(
                ImVec4(0.75f, 0.1f, 0.1f, 1.0f),
                "%s",
                message.c_str()
            );
            ImGui::SetWindowFontScale(1.3f);

            ImGui::EndChild();

            ImGui::PopStyleColor();
        }
        else
        {
            ImGui::PushStyleColor(
                ImGuiCol_ChildBg,
                ImVec4(0.82f, 0.94f, 0.82f, 1.0f)
            );

            ImGui::BeginChild(
                "SuccessBanner",
                ImVec2(0, 50),
                true
            );
            ImGui::SetWindowFontScale(1.3f);

            ImGui::TextColored(
                ImVec4(0.05f, 0.45f, 0.15f, 1.0f),
                "%s",
                message.c_str()
            );
            ImGui::SetWindowFontScale(1.3f);

            ImGui::EndChild();

            ImGui::PopStyleColor();
        }
    }

    ImGui::EndChild();

    ImGui::PopStyleVar();
}