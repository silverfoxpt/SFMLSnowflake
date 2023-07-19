#include <SFML/Graphics.hpp>

#include "Reuseable/gameManager.h"
#include "Reuseable/randomsfml.h"
#include "Reuseable/math.h"

#include "Brownian/brownian.h"
#include "Lattice/lattice.h"
#include "Lattice/crystal.h"

#include "IMGUI/imgui-SFML.h"

//really early stuff initialization
Rand Randomize::rand;

//public vars
sf::RenderWindow window(sf::VideoMode(800, 800), "SFML Snowflake");

float GameManager::windowWidth                  = window.getSize().x;
float GameManager::windowHeight                 = window.getSize().y;
float GameManager::deltaTime                    = 1/300.0;

sf::Vector2u GameManager::mainWindowSize        = sf::Vector2u(800, 800);
sf::Vector2u GameManager::originalResolution    = sf::Vector2u(1920, 1080);

//game-related var
Brownian brownianManager;
HexagonLattice lattice;
Crystal crystal;

//test vars

void Test() {
    
}

void UpdateTest() {
    
}

void VisualizeTest() {
    
}

void Initialize() {
    Test();

    GameManager::InitializeWindowWithResolution(&window);
    brownianManager.Initialize(&window);
    lattice.Initialize(&window);
    crystal.Initialize(&window, &lattice);
}

void Update(sf::Event event) {
    UpdateTest();

    //brownianManager.Update(event);
    lattice.Update(event);
    crystal.Update(event);
}

void Visualize(sf::Event event) {
    VisualizeTest();

    brownianManager.Visualize(event);
    lattice.Visualize(event);
    crystal.Visualize(event);
}

void LateUpdate(sf::Event event) {
    brownianManager.LateUpdate();
    lattice.LateUpdate();
    crystal.LateUpdate();
}

void Reset() {
    brownianManager.Reset();
    lattice.Reset();
    crystal.Reset();
}

void MainGameLoop() {
    //polling event
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }

    window.clear();

    //doin stuff zone
    Update(event);
    Visualize(event);
    LateUpdate(event);

    window.display();
}

int main()
{
    Initialize();
    while (window.isOpen())
    {
        MainGameLoop();    
    }

    return 0;
}