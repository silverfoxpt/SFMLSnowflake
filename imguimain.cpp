#include "imguimain.h"

void ImguiMain::ImGuiMainLoop() {
    ImGui::Begin("Settings");

    //choose mode
    const char* items[] = { "Snow crystal"};
    static int item_current_idx = 0; 
    const char* combo_preview_value = items[item_current_idx]; 
    if (ImGui::BeginCombo("Mode##modecombo", combo_preview_value, 0))
    {
        for (int n = 0; n < IM_ARRAYSIZE(items); n++)
        {
            const bool is_selected = (item_current_idx == n);
            if (ImGui::Selectable(items[n], is_selected))
                item_current_idx = n;

            // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
            if (is_selected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }    

    if (item_current_idx == 0) { //snow crystal
        SnowCrystal();
    }

    ImGui::End();
}

void ImguiMain::SnowCrystal() {
    ImGui::Spacing();
    
}