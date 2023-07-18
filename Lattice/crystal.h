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

        std::vector<Hexagon*> inside;
        std::vector<Hexagon*> boundary;
        std::vector<Hexagon*> outside;
        std::vector<Hexagon*> outsideBoundary;

        //settings
        float p1 = 0.35;

        float k2 = 0.05;

        float b3 = 1.4;

        void Initialize(sf::RenderWindow* window, HexagonLattice* lattice) override;
        void Update(sf::Event event) override;
        void Visualize(sf::Event event) override;
        void LateUpdate() override;
        void Reset() override;

    private:
        void Diffusion();
        void Freezing();
        void Attachment();
};

#endif