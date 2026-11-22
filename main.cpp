#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>
#include <iostream> // std::cout
#include "settings.h"
#include "dashboard.h"

#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_opengl3.h"

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
    Global::gBoldFont = io.Fonts->AddFontFromFileTTF(
        "fonts/georgiab.ttf",
        16.0f
    );

    if (Global::gBoldFont == nullptr)
    {
        std::cout << "Georgia Bold Font Loading Failed!" << std::endl;
        return -1;
    }
    else
    {
        std::cout << "Georgia Bold Font Loaded Successfully!" << std::endl;
    }

    Global::numFont = io.Fonts->AddFontFromFileTTF(
        "fonts/segoeui.ttf",
        18.0f
    );

    if (Global::numFont == nullptr)
    {
        std::cout << "Segoe UI Number Font Loading Failed!" << std::endl;
        return -1;
    }
    else
    {
        std::cout << "Segoe UI Number Font Loaded Successfully!" << std::endl;
    }

  
    Settings::SetupCoffeeTheme();
    if (Settings::Load_csv())
    {
        std::cout << "'data.csv' Loaded Succefully!" << std::endl;
    }
    else
    {
        std::cout << "'data.csv' Cannot be Loaded" << std::endl;
        return -1;
    }
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

        ImGui::SetWindowFontScale(1.45f);

        ImGui::PushFont(Global::gBoldFont);

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
        ImGui::PushFont(Global::gBoldFont);
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
        Load_dashboardPage();
        
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