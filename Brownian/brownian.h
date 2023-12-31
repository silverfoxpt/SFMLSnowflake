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

enum BrownianTravelPhase {
    Waiting = 0,
    Travelling = 1
};

class Brownian : public Monobehaviour<sf::RenderWindow*> {
    public:
        //settings
        float maxDistanceFromCenter         = 350;
        sf::Vector2f center                 = sf::Vector2f(400, 400);
        sf::Vector2f offset                 = sf::Vector2f(0, -75);

        int totalParticlePerQuadrant        = 500; // if -1 then unlimited
        int totalNumQuadrant                = 6;

        float particleSpeed                 = 2; //per frame update
        float particleRadius                = 2; 
        float detectionRadius               = 2; //let things stick a bit

        //used vars
        std::vector<sf::Vector2f> points;
        std::vector<sf::Vector2f> currentStickedPoints;

        sf::Vector2f currentMovingPoint;
        sf::Vector2f centerPoint;

        sf::VertexArray vertices;

        BrownianTravelPhase phase = BrownianTravelPhase::Waiting;

        sf::RenderWindow* window;

        void Initialize(sf::RenderWindow* window) override;
        void Update(sf::Event event)        override;
        void Visualize(sf::Event event)     override;
        void LateUpdate()                   override;
        void Reset()                        override; 

        void CalculateVertices(sf::VertexArray &array, sf::Vector2f point, sf::Color color);

        float* getMaxDistanceFromCenter()   { return &this->maxDistanceFromCenter;}
        float* getCenterX()                 { return &this->center.x; }
        float* getCenterY()                 { return &this->center.y; }
        float* getOffsetX()                 { return &this->offset.x; }
        float* getOffsetY()                 { return &this->offset.y; }
        int* getNumParticlePerQuadrant()    { return &this->totalParticlePerQuadrant;}
        int* getTotalNumQuadrant()          { return &this->totalNumQuadrant;}
};  

#endif