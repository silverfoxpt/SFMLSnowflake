#ifndef H_BROWNIAN
#define H_BROWNIAN

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

enum BrownianTravalPhase {
    Waiting = 0,
    Travelling = 1
};

class Brownian : public Monobehaviour<sf::RenderWindow*> {
    public:
        //settings
        float maxDistanceFromCenter         = 400;
        sf::Vector2f center                 = sf::Vector2f(400, 400);

        int totalParticlePerQuadrant        = 400; // if -1 then unlimited
        int totalNumQuadrant                = 6;

        float particleSpeed                 = 1; //per frame update
        float particleRadius                = 5; 

        //used vars
        std::vector<sf::Vector2f> points;
        std::vector<sf::Vector2f> currentStickedPoints;
        sf::Vector2f currentMovingPoint;
        sf::Vector2f centerPoint;

        BrownianTravalPhase phase = BrownianTravalPhase::Waiting;

        sf::RenderWindow* window;

        void Initialize(sf::RenderWindow* window) override;
        void Update(sf::Event event)        override;
        void Visualize(sf::Event event)     override;
        void LateUpdate()                   override;
        void Reset()                        override;
};  

#endif