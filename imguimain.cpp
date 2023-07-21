#include "imguimain.h"

void ImguiMain::Initialize(HexagonLattice* lattice, Crystal* crystal, sf::RenderWindow* window) {
    this->myLattice = lattice;
    this->myCrystal = crystal;
    this->window = window;
}

void ImguiMain::ImGuiMainLoop() {
    //ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_NavEnableGamepad;
    Settings();
}

//custom
void ImguiMain::Settings() {
    ImGui::Begin("Settings");

    //choose mode
    char* items[] = { "Snow crystal"};
    int item_current_idx = 0; 
    ComboBox("Mode##combomode", items, item_current_idx, IM_ARRAYSIZE(items));

    if (item_current_idx == 0) { //snow crystal
        if (ImGui::Button("Restart")) {
            myLattice->Reset();
            myCrystal->Reset();

            myLattice->Initialize(window);
            myCrystal->Initialize(window, myLattice);
        }
        SnowCrystal();
    }
    ImGui::End();
}

void ImguiMain::SnowCrystal() {
    ImGui::Text("Size settings");
    ImGui::SetNextItemWidth(150); ImGui::InputFloat("Hexagon cell diameter", myLattice->getHexSize());
    ImGui::SetNextItemWidth(150); ImGui::InputInt("Number of columns", myLattice->getNumCols()); 
    ImGui::SetNextItemWidth(150); ImGui::InputInt("Number of rows", myLattice->getNumRows());

    ImGui::Text("Crystal settings");
    ImGui::SetNextItemWidth(150); ImGui::InputFloat("rho", myCrystal->getP1());     ImGui::SameLine(150 + 100);
    ImGui::SetNextItemWidth(150); ImGui::InputFloat("kappa", myCrystal->getK2());   
    ImGui::SetNextItemWidth(150); ImGui::InputFloat("beta", myCrystal->getB3());    ImGui::SameLine(150 + 100);
    ImGui::SetNextItemWidth(150); ImGui::InputFloat("theta", myCrystal->getO3());   
    ImGui::SetNextItemWidth(150); ImGui::InputFloat("alpha", myCrystal->getA3());   ImGui::SameLine(150 + 100);
    ImGui::SetNextItemWidth(150); ImGui::InputFloat("mu", myCrystal->getU4());      
    ImGui::SetNextItemWidth(150); ImGui::InputFloat("gamma", myCrystal->getY4());   ImGui::SameLine(150 + 100);
    ImGui::SetNextItemWidth(150); ImGui::InputFloat("sigma", myCrystal->getO5());   
}

//templates
void ImguiMain::ComboBox(const char* label, char* items[], int& item_current_idx, int item_size) {
    char* combo_preview_value = items[item_current_idx]; 
    if (ImGui::BeginCombo(label, combo_preview_value, 0))
    {
        for (int n = 0; n < item_size; n++)
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