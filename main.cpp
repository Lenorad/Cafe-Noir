#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>
#include <iostream>
#include "CustomerInput.h"

#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_opengl3.h"
ImFont* gBoldFont = nullptr;
ImFont* numFont = nullptr;


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

int main(int argc, char* argv[]) {
    // 1. SDL Initialization
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cout << "SDL Initialization Failed: " << SDL_GetError() << std::endl;
        return -1;
    }

    // 2. OpenGL Attribute Set 
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // 3.  Create Window 
    SDL_Window* window = SDL_CreateWindow("C++ Project", 1280, 780, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (!window) {
        std::cout << "Window Creation Failed: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    if (!gl_context) {
        std::cout << "OpenGL Context Creation Failed: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    SDL_GL_MakeCurrent(window, gl_context);
    SDL_GL_SetSwapInterval(1); //  To Open Vsync 

    // 4.  Build Dear ImGui Context 
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    // Load Fonts
    gBoldFont = io.Fonts->AddFontFromFileTTF(
        "fonts/georgiab.ttf",
        16.0f
    );

    if (gBoldFont == nullptr)
    {
        std::cout << "Georgia Bold Font Loading Failed!" << std::endl;
    }
    else
    {
        std::cout << "Georgia Bold Font Loaded Successfully!" << std::endl;
    }

    numFont = io.Fonts->AddFontFromFileTTF(
        "fonts/segoeui.ttf",
        18.0f
    );

    if (numFont == nullptr)
    {
        std::cout << "Segoe UI Number Font Loading Failed!" << std::endl;
    }
    else
    {
        std::cout << "Segoe UI Number Font Loaded Successfully!" << std::endl;
    }

    SetupCoffeeTheme();
    io.FontGlobalScale = 1.20f;


    // 5. ImGui SDL3 & OpenGL3 Backends Initialization 
    ImGui_ImplSDL3_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init("#version 130");

    Customer customers[MAX_CUSTOMERS] = {};
    int customerCount = 0;
    bool done = false;
    while (!done) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL3_ProcessEvent(&event);
            if (event.type == SDL_EVENT_QUIT)
                done = true;
        }

        //  Start ImGui New Frame 
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        //  Show Demo Window 
        //bool show_demo_window = true;
        //ImGui::ShowDemoWindow(&show_demo_window);

        //  Struct Custom Window
      // Main Dashboard
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(io.DisplaySize);

        ImGui::Begin("CafeNoirRoot",
            nullptr,
            ImGuiWindowFlags_NoTitleBar |
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoSavedSettings);

        // =========================
        // HEADER
        // =========================
        ImGui::SetWindowFontScale(1.45f);

        ImGui::PushFont(gBoldFont);

        ImGui::TextColored(
            ImVec4(0.96f, 0.87f, 0.74f, 1.0f),
            "CAFE NOIR"
        );

        ImGui::PopFont();

        ImGui::SetWindowFontScale(1.0f);


        // Coffee bean decorations
        ImDrawList* draw = ImGui::GetWindowDrawList();
        ImVec2 winPos = ImGui::GetWindowPos();

        float right = ImGui::GetWindowWidth();

        draw->AddCircleFilled(
            ImVec2(winPos.x + right - 55, winPos.y + 27),
            9,
            IM_COL32(110, 72, 43, 255)
        );

        draw->AddLine(
            ImVec2(winPos.x + right - 59, winPos.y + 21),
            ImVec2(winPos.x + right - 51, winPos.y + 33),
            IM_COL32(225, 190, 150, 255),
            2.0f
        );

        draw->AddCircleFilled(
            ImVec2(winPos.x + right - 28, winPos.y + 27),
            9,
            IM_COL32(110, 72, 43, 255)
        );

        draw->AddLine(
            ImVec2(winPos.x + right - 32, winPos.y + 21),
            ImVec2(winPos.x + right - 24, winPos.y + 33),
            IM_COL32(225, 190, 150, 255),
            2.0f
        );

        ImGui::Separator();
        ImGui::Spacing();

        // =========================
        // SIDEBAR
        // =========================

        ImGui::BeginChild(
            "Sidebar",
            ImVec2(210, 0),
            true
        );

        ImGui::Spacing();

        ImGui::SetWindowFontScale(1.35f);
        ImGui::PushFont(gBoldFont);
        ImGui::Text("MENU");
        ImGui::PopFont();
        ImGui::SetWindowFontScale(1.0f);

        ImGui::Separator();
        ImGui::Spacing();

        ImGui::PushStyleColor(
            ImGuiCol_Text,
            ImVec4(1.0f, 1.0f, 1.0f, 1.0f)
        );

        ImGui::SetWindowFontScale(1.2f);

        ImGui::Button("Dashboard", ImVec2(-1, 45));

        ImGui::Spacing();

        ImGui::Button("Customers", ImVec2(-1, 45));

        ImGui::Spacing();

        ImGui::Button("Analysis", ImVec2(-1, 45));

        ImGui::SetWindowFontScale(1.0f);

        ImGui::PopStyleColor();

        // Sidebar footer
        ImGui::SetCursorPosY(
            ImGui::GetWindowHeight() - 65
        );

        ImGui::Separator();

        ImGui::EndChild();

        ImGui::SameLine();

        // =========================
        // MAIN CONTENT
        // =========================

        ImGui::BeginChild(
            "MainContent",
            ImVec2(0, 0),
            true
        );

        ImGui::Spacing();

        ImGui::SetWindowFontScale(1.35f);
        ImGui::PushFont(gBoldFont);
        ImGui::Text("Welcome to Cafe Noir!");
        ImGui::PopFont();
        ImGui::SetWindowFontScale(1.0f);

        ImGui::PushFont(gBoldFont);
        ImGui::Text("Customer Management Dashboard");
        ImGui::PopFont();

        ImGui::Separator();
        ImGui::Spacing();

        ImGui::SetWindowFontScale(1.15f);

        ImGui::Text("Total Customers:");
        ImGui::SameLine(0.0f, 4.0f);
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 2.0f);
        if (numFont) ImGui::PushFont(numFont);
        ImGui::Text("%d", customerCount);
        if (numFont) ImGui::PopFont();

        ImGui::SetWindowFontScale(1.0f);

        ImGui::Spacing();

        // Customer Input Section
        RenderCustomerInput(customers, customerCount);

        ImGui::EndChild();

        ImGui::End();

        // Rendering
        ImGui::Render();
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        glClearColor(0.35f, 0.22f, 0.14f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        SDL_GL_SwapWindow(window);
    }

    // Cleanup 
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DestroyContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}