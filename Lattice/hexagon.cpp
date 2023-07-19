#include "hexagon.h"

void Hexagon::Initialize(sf::RenderWindow* window, float size, sf::Vector2f screenPos, int col, int row) {
    this->size = size;
    this->screenPos = screenPos;
    this->window = window;

    this->vertexArr = sf::VertexArray(sf::TrianglesFan);

    this->col = col;
    this->row = row;

    //create the shape
    const float angle = 2 * 3.14159 / 6; // Angle between each corner of the hexagon
    const float radius = size / 2.0f;    // Radius of the circumscribed circle

    this->originalColor = sf::Color::White;
    this->vertexArr.append(sf::Vertex(screenPos, originalColor)); // Center of the hexagon

    for (int i = 0; i <= 6; ++i) {
        sf::Vector2f point(screenPos.x + radius * cos(i * angle),
                            screenPos.y + radius * sin(i * angle));
        this->vertexArr.append(sf::Vertex(point, originalColor));
    }
}

void Hexagon::Update(sf::Event event) {
}

void Hexagon::Visualize(sf::Event event) {

}

void Hexagon::LateUpdate() {

}

void Hexagon::Reset() {
    this->vertexArr.clear();
    this->neighborHex.clear();
}

void Hexagon::ChangeColor(sf::Color color) {
    for (int i = 0; i < (int) this->vertexArr.getVertexCount(); i++) {
        this->vertexArr[i].color = color;
    }
}

void Hexagon::ChangeToOriginalColor() {
    this->ChangeColor(this->originalColor);
}