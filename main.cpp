#include <SFML/Graphics.hpp>

#include "Reuseable/gameManager.h"
#include "Reuseable/randomsfml.h"
#include "Reuseable/math.h"

#include "Brownian/brownian.h"
#include "Lattice/lattice.h"
#include "Lattice/crystal.h"

#include "imguimain.h"

//really early stuff initialization
Rand Randomize::rand;

//public vars
sf::RenderWindow window(sf::VideoMode(800, 800), "SFML Snowflake");

float GameManager::windowWidth                  = window.getSize().x;
float GameManager::windowHeight                 = window.getSize().y;
float GameManager::deltaTime                    = 1/300.0;

sf::Vector2u GameManager::mainWindowSize        = sf::Vector2u(800, 800);
sf::Vector2u GameManager::originalResolution    = sf::Vector2u(1920, 1080);

sf::Clock deltaTime;

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
    ImGui::SFML::SetCurrentWindow(window);

    //polling event
    sf::Event event;
    while (window.pollEvent(event))
    {
        ImGui::SFML::ProcessEvent(window, event);
        if (event.type == sf::Event::Closed)
            window.close();
    }
    ImGui::SFML::Update(window, deltaTime.restart());
    window.clear();

    //doin stuff zone
    Update(event);
    Visualize(event);

    ImguiMain::ImGuiMainLoop();

    LateUpdate(event);

    //display
    ImGui::SFML::Render(window);
    window.display();
}

int main()
{
    ImGui::SFML::Init(window);
    ImGui::GetIO().IniFilename = "imgui.ini";

    Initialize();
    while (window.isOpen())
    {
        MainGameLoop();    
    }

    ImGui::SFML::Shutdown(window);
    return 0;
}