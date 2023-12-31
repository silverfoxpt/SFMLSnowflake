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
        sf::Vector2f startingPos;
        float offsetX = 0, offsetY = -100;
        float hexSize = 3.0f;
        int numRows = 199;
        int numCols = 199;

        //actual used vars
        std::vector<std::vector<Hexagon>> hexagons; //col first, row later

        void Initialize(sf::RenderWindow* window) override;
        void Update(sf::Event event) override;
        void Visualize(sf::Event event) override;
        void LateUpdate() override;
        void Reset() override;

        Hexagon* getMidHex();
        Hexagon* getHexAtIndex(int col, int row);

        float* getHexSize() { return &this->hexSize; }
        int* getNumRows() { return &this->numRows; }
        int* getNumCols() { return &this->numCols; }

        float* getOffsetX() { return &this->offsetX; }
        float* getOffsetY() { return &this->offsetY; }

    private:
        Hexagon createHexagon(float size, sf::Vector2f position, int col, int row);
        Hexagon* getHexAtPos(float x, float y);

};

#endif