#include "lattice.h"

void HexagonLattice::Initialize(sf::RenderWindow* window) {
    this->window = window;

    //create hex
    float radius = this->hexSize / 2.0f;
    float spaceBetweenCrack = (radius / 2.0f) * (std::tan(Math::toRad(15))) * 2;
    float height = sqrt(radius * radius - (radius/2) * (radius/2));

    for (int col = 0; col < numCols; ++col) {
        for (int row = 0; row < numRows; ++row) {
            float x = col * (radius * 1.5f);
            float y = this->hexSize * (row) - (row * spaceBetweenCrack) + ((col % 2) * height);
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