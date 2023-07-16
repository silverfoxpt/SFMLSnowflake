#include "lattice.h"

void HexagonLattice::Initialize(sf::RenderWindow* window) {
    this->window = window;

    //create hex
    const float hexSize = 50.0f;
    const int numRows = 5;
    const int numCols = 7;

    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            float x = hexSize * col * 1.5f;
            float y = hexSize * (row + 0.5f * (col % 2));
            this->hexagons.push_back(createHexagon(hexSize, sf::Vector2f(x, y)));
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

Hexagon HexagonLattice::createHexagon(float size, sf::Vector2f position) {
    Hexagon hex;
    hex.Initialize(this->window, size, position);

    return hex;
}