#include "Menu.h"
#include "../External/ImGui/imgui.h"
#include "../External/ImGui/imgui_internal.h"
#include "../External/Font/font.h"
#include "../Utils/skcrypt.h"

namespace Menu
{
    void Menu::Init()
    {
        static const ImWchar ranges[] =
        {
            0x0020, 0x00FF,
            0x0400, 0x044F,
            0,
        };
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        ImFontConfig cfg;
        cfg.FontDataOwnedByAtlas = false;
        cfg.FontBuilderFlags;

        g_Font = io.Fonts->AddFontFromMemoryTTF(font, sizeof(font), 14.f, &cfg, ranges);

        ImGuiStyle& style = ImGui::GetStyle();
        style.FrameRounding = 2.5; .0f;
        style.WindowBorderSize = 0.0f;
        style.WindowPadding = ImVec2(8, 8);
        style.FramePadding = ImVec2(10, 4);
        style.WindowRounding = 4.0f;

        style.Colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 0.95f);
        style.Colors[ImGuiCol_Button] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
        style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);
        style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
        style.Colors[ImGuiCol_Border] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
    }

    void Menu::Render()
    {
        static bool optionA = false;
        static bool optionB = true;
        static float sliderValue = 0.5f;
        static int currentMode = 0;
        static const char* modes[] = { "Basic", "Advanced", "Expert" };

        ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);

        ImGui::Begin(skCrypt("Demo Settings").decrypt(), nullptr,
            ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_AlwaysAutoResize |
            ImGuiWindowFlags_NoScrollbar);

        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(skCrypt("ImGui Example Menu").decrypt()).x) * 0.5f);
        ImGui::Text(skCrypt("ImGui Example Menu").decrypt());
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::Checkbox(skCrypt("Enable Option A").decrypt(), &optionA);
        ImGui::Spacing();

        ImGui::Checkbox(skCrypt("Enable Option B").decrypt(), &optionB);
        ImGui::Spacing();

        ImGui::Text(skCrypt("Adjust Value:").decrypt());
        ImGui::SliderFloat(skCrypt("##slider").decrypt(), &sliderValue, 0.0f, 1.0f, "%.2f");
        ImGui::Spacing();

        ImGui::Text(skCrypt("Select Mode:").decrypt());
        ImGui::Combo(skCrypt("##combo").decrypt(), &currentMode, modes, IM_ARRAYSIZE(modes));
        ImGui::Spacing();
        ImGui::Spacing();

        if (ImGui::Button(skCrypt("Apply Settings").decrypt(), ImVec2(-1.0f, 40.0f)))
        {
            // Action button
        }

        ImGui::End();
    }
}
