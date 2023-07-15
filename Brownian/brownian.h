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

enum BrownianTravalPhase {
    Waiting = 0,
    Travelling = 1
};

class Brownian : public Monobehaviour<> {
    public:
        //settings
        float maxDistanceFromCenter         = 400;
        sf::Vector2f center                 = sf::Vector2f(400, 400);

        int totalParticlePerQuadrant        = 400; // if -1 then unlimited
        int totalNumQuadrant                = 6;

        float partileSpeed                  = 10; //per frame update

        //used vars
        std::vector<sf::Vector2f> points;
        std::vector<sf::Vector2f> currentStickedPoints;

        BrownianTravalPhase phase = BrownianTravalPhase::Waiting;

        void Initialize()                   override;
        void Update(sf::Event event)        override;
        void Visualize(sf::Event event)     override;
        void LateUpdate()                   override;
        void Reset()                        override;
};  

#endif