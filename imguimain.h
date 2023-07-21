#ifndef H_IMGUIMAIN
#define H_IMGUIMAIN

#include <SFML/Graphics.hpp>

#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <memory>
#include <chrono>

#include "IMGUI/imgui.h"
#include "IMGUI/imgui-SFML.h"

#include "Lattice/crystal.h"
#include "Lattice/lattice.h"

class ImguiMain {
    public:
        static void ImGuiMainLoop();

        //custom variables - don't copy this!
        static HexagonLattice* myLattice;
        static Crystal* myCrystal;

    private:
        //template
        static int ComboBox(const char* label, char* items[], int& item_current_idx);

        //custom methods - don't copy this!
        static void Settings();
        static void SnowCrystal();

};

#endif