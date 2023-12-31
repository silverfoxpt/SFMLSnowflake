#ifndef H_HEXAGON
#define H_HEXAGON

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
#include "../Reuseable/randomsfml.h"

class Hexagon: Monobehaviour<sf::RenderWindow*, float, sf::Vector2f, int, int> {
    public:
        sf::RenderWindow* window;

        //used vars
        int layer;

        sf::Vector2f screenPos;
        float size;
        sf::VertexArray vertexArr;

        std::vector<Hexagon*> neighborHex;

        //test vars
        sf::Color originalColor = sf::Color::White;
        int col;
        int row;

        void Initialize(sf::RenderWindow* window, float size, sf::Vector2f screenPos, int col, int row) override;
        void Update(sf::Event event) override;
        void Visualize(sf::Event event) override;
        void LateUpdate() override;
        void Reset() override;

        void ChangeColor(sf::Color color);
        void ChangeToOriginalColor();

    private:
        
};

#endif