#include "brownian.h"

void Brownian::Initialize() {
    //populate point and their position
    for (int i = 0; i < this->totalParticlePerQuadrant; i++) {
        //randomize a position (around center)
        sf::Vector2f point = this->center + Math::scaleVec(Math::getRandomDirectionVecWithAngleRange(0, 360.0 / this->totalNumQuadrant), this->maxDistanceFromCenter);

        this->points.push_back(point);
    }

    //check if unlimited points
    if (this->totalParticlePerQuadrant == -1) {
        //seed the first travelling point
        sf::Vector2f point = this->center + Math::scaleVec(Math::getRandomDirectionVecWithAngleRange(0, 360.0 / this->totalNumQuadrant), this->maxDistanceFromCenter);

        this->points.push_back(point);
    }

    //initialize a seed point
    sf::Vector2f point = center;
    this->currentStickedPoints.push_back(point);
}

void Brownian::Update(sf::Event event) {
    if (this->points.empty()) {
        return;
    }

    if (this->phase == BrownianTravalPhase::Waiting) { //start a new point travelling!

    }
}

void Brownian::Visualize(sf::Event event) {

}

void Brownian::LateUpdate() {

}

void Brownian::Reset() {
    points.clear();
    currentStickedPoints.clear();
}