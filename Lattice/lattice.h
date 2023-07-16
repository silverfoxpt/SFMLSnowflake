#ifndef H_LATTICE
#define H_LATTICE

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

#include "hexagon.h"

class HexagonLattice : Monobehaviour<sf::RenderWindow*> {
    public:
        sf::RenderWindow* window;

        //settings
        sf::Vector2f startingPos = sf::Vector2f(70, 70);
        float hexSize = 50.0f;
        int numRows = 5;
        int numCols = 4;

        //actual used vars
        std::vector<Hexagon> hexagons;

        void Initialize(sf::RenderWindow* window) override;
        void Update(sf::Event event) override;
        void Visualize(sf::Event event) override;
        void LateUpdate() override;
        void Reset() override;

    private:
        Hexagon createHexagon(float size, sf::Vector2f position);

};

#endif