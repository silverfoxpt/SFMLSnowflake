#include "lattice.h"

void HexagonLattice::Initialize(sf::RenderWindow* window) {
    this->window = window;

    //create hex
    for (int col = 0; col < numCols; ++col) {
        for (int row = 0; row < numRows; ++row) {
            float x = hexSize * col * 0.75f;
            float y = hexSize * (row + 0.5f * (col % 2));
            this->hexagons.push_back(createHexagon(hexSize, this->startingPos + sf::Vector2f(x, y)));
        }
    }
}

void HexagonLattice::Update(sf::Event event) {
    for (const auto& hexagon : hexagons) {
        this->window->draw(hexagon.vertexArr);
    }
}

void HexagonLattice::Visualize(sf::Event event) {

}

void HexagonLattice::LateUpdate() {

}

void HexagonLattice::Reset() {
    this->hexagons.clear();
}

Hexagon HexagonLattice::createHexagon(float size, sf::Vector2f screenPos) {
    Hexagon hex;
    hex.Initialize(this->window, size, screenPos);

    return hex;
}