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

class Brownian : public Monobehaviour<> {
    public:
        float maxDistanceFromCenter         = 400;
        sf::Vector2f center                 = sf::Vector2f(400, 400);
        int totalParticlePerQuadrant        = 400; // if -1 then unlimited
        float partileSpeed                  = 10; //per frame update

        void Initialize()                   override;
        void Update(sf::Event event)        override;
        void Visualize(sf::Event event)     override;
        void LateUpdate()                   override;
};  

#endif