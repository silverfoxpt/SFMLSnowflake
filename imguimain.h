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

class ImguiMain {
    public:
        static void ImGuiMainLoop();

    private:
        static void SnowCrystal();

};

#endif