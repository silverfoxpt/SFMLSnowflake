#include "imguimain.h"

void ImguiMain::ImGuiMainLoop() {
    Settings();
}

//custom
void ImguiMain::Settings() {
    ImGui::Begin("Settings");

    //choose mode
    char* items[] = { "Snow crystal"};
    int item_current_idx = 0; 
    ComboBox("Mode##combomode", items, item_current_idx);

    if (item_current_idx == 0) { //snow crystal
        SnowCrystal();
    }

    ImGui::End();
}

void ImguiMain::SnowCrystal() {
    ImGui::Spacing();

    ImGui::Text("Size settings");
    ImGui::InputFloat("Hexagon cell diameter", myLattice->getHexSize());
    ImGui::InputInt("Number of columns", myLattice->getNumCols());
    ImGui::InputInt("Number of rows", myLattice->getNumRows());

    ImGui::Spacing();
    ImGui::Text("Crystal settings");
    ImGui::InputFloat("\u03C1", myCrystal->getP1());
}

//templates
int ImguiMain::ComboBox(const char* label, char* items[], int& item_current_idx) {
    char* combo_preview_value = items[item_current_idx]; 
    if (ImGui::BeginCombo(label, combo_preview_value, 0))
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
}