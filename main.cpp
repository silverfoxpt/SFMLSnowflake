#include <SFML/Graphics.hpp>

#include "Reuseable/gameManager.h"
#include "Reuseable/randomsfml.h"

//really early stuff initialization
Rand Randomize::rand;

//public vars
sf::RenderWindow window(sf::VideoMode(800, 800), "SFML Snowflake");

float GameManager::windowWidth              = window.getSize().x;
float GameManager::windowHeight             = window.getSize().y;
float GameManager::deltaTime                = 1/300.0;

sf::Vector2u GameManager::mainWindowSize    = sf::Vector2u(800, 800);
sf::Vector2u GameManager::originalResolution = sf::Vector2u(1920, 1080);

int main()
{
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}