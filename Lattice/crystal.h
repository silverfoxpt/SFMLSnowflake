#ifndef H_CRYSTAL
#define H_CRYSTAL

#include <SFML/Graphics.hpp>

#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <memory>
#include <chrono>
#include <set>
#include <unordered_set>

#include "../Reuseable/templateclass.h"
#include "../Reuseable/math.h"
#include "../Reuseable/drawshapes.h"
#include "../Reuseable/gameManager.h"

#include "lattice.h"

class Crystal: Monobehaviour<sf::RenderWindow*, HexagonLattice*> {
    public:
        sf::RenderWindow* window;
        HexagonLattice* lattice;

        int cols;
        int rows;

        //values
        std::vector<std::vector<int>> a;
        std::vector<std::vector<float>> b;
        std::vector<std::vector<float>> c;
        std::vector<std::vector<float>> d;
        //std::vector<std::vector<float>> d2;

        std::vector<Hexagon*> inside;
        std::vector<Hexagon*> boundary;
        std::vector<Hexagon*> outside;
        std::vector<Hexagon*> outsideBoundary;
        std::vector<Hexagon*> all;

        //settings
        float p1 = 0.35;

        float k2 = 0.05;

        float b3 = 1.4;
        float o3 = 0.015;
        float a3 = 0.001;

        float u4 = 0.015;
        float y4 = 0.01;

        float o5 = 0.00005;

        void Initialize(sf::RenderWindow* window, HexagonLattice* lattice) override;
        void Update(sf::Event event) override;
        void Visualize(sf::Event event) override;
        void LateUpdate() override;
        void Reset() override;

    private:
        void Diffusion();
        void Freezing();
        void Attachment();
        void Melting();
        void Perturb();

        void AddToCrystal(int col, int row);
        void ModCrystalValue(int col, int row);
};

#endif