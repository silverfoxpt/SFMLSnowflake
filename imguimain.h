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
#include "Brownian/brownian.h"

enum CurrentChoice {
    CrystalSnow = 0,
    BrownianSnow = 1
};

class ImguiMain {
    public:
        void Initialize(HexagonLattice* lattice, Crystal* crystal, sf::RenderWindow* window, Brownian* brownian);
        void ImGuiMainLoop();

        //custom variables - don't copy this!
        HexagonLattice* myLattice;
        Crystal* myCrystal;
        Brownian* brownian;

        sf::RenderWindow* window;

        //used by others
        CurrentChoice choice = CurrentChoice::CrystalSnow;
        int item_current_idx = 0;

    private:
        //template
        void ComboBox(const char* label, char* items[], int& item_current_idx, int item_size);

        //custom methods - don't copy this!
        void Settings();
        void SnowCrystal();
        void BrownianSnow();

        void RestartCrystal();
        void RestartBrownian();

};

#endif