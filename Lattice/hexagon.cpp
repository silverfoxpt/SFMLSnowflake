#include "hexagon.h"

void Hexagon::Initialize(sf::RenderWindow* window, float size, sf::Vector2f screenPos) {
    this->size = size;
    this->screenPos = screenPos;
    this->window = window;

    this->vertexArr = sf::VertexArray(sf::TrianglesFan);

    //create the shape
    const float angle = 2 * 3.14159 / 6; // Angle between each corner of the hexagon
    const float radius = size / 2.0f;    // Radius of the circumscribed circle

    this->vertexArr.append(sf::Vertex(screenPos, sf::Color::White)); // Center of the hexagon

    for (int i = 0; i <= 6; ++i) {
        sf::Vector2f point(screenPos.x + radius * cos(i * angle),
                           screenPos.y + radius * sin(i * angle));
        this->vertexArr.append(sf::Vertex(point, sf::Color::White));
    }
}

void Hexagon::Update(sf::Event event) {
}

void Hexagon::Visualize(sf::Event event) {

}

void Hexagon::LateUpdate() {

}

void Hexagon::Reset() {

}