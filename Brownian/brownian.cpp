#include "brownian.h"

void Brownian::Initialize(sf::RenderWindow* window) {
    this->window = window;
    this->centerPoint = GameManager::convertScreenToWorld(center);

    //populate point and their position
    for (int i = 0; i < this->totalParticlePerQuadrant; i++) {
        //randomize a position (around center)
        sf::Vector2f point = this->centerPoint + 
            Math::scaleVec(Math::getRandomDirectionVecWithAngleRange(0, 360.0 / this->totalNumQuadrant), this->maxDistanceFromCenter);

        this->points.push_back(point);
    }

    //check if unlimited points
    if (this->totalParticlePerQuadrant == -1) {
        //seed the first travelling point
        sf::Vector2f point = this->centerPoint + 
            Math::scaleVec(Math::getRandomDirectionVecWithAngleRange(0, 360.0 / this->totalNumQuadrant), this->maxDistanceFromCenter);

        this->points.push_back(point);
    }

    //initialize a seed point
    sf::Vector2f point = this->centerPoint;
    this->currentStickedPoints.push_back(point);
}

void Brownian::Update(sf::Event event) {
    if (this->points.empty() && BrownianTravalPhase::Waiting) {
        return;
    }

    if (this->phase == BrownianTravalPhase::Waiting) { //start a new point travelling!
        sf::Vector2f point = this->points.back(); this->points.pop_back();
        this->currentMovingPoint = point;

        this->phase = BrownianTravalPhase::Travelling;
    } else { //travelling!
        //check if intersect any sticky circle
        for (auto stick: this->currentStickedPoints) {
            if (Math::CircleIntersect(stick, this->particleRadius, this->currentMovingPoint, this->particleRadius)) { //finished travelling!
                this->currentStickedPoints.push_back(this->currentMovingPoint);
                this->phase = BrownianTravalPhase::Waiting;

                //check if infinite points
                if (this->totalParticlePerQuadrant == -1) {
                    //seed another travelling point
                    sf::Vector2f point = this->centerPoint + Math::scaleVec(Math::getRandomDirectionVecWithAngleRange(0, 360.0 / this->totalNumQuadrant), this->maxDistanceFromCenter);

                    this->points.push_back(point);
                }
                return;
            }
        }

        //random walk
        //calculate range of x movement
        float start = this->centerPoint.x;
        float end = this->centerPoint.x + std::tan(Math::toRad(360.0 / this->totalNumQuadrant)) * std::abs(this->currentMovingPoint.y - GameManager::convertScreenToWorld(this->center).y);

        sf::Vector2f dirToCenter = this->centerPoint - this->currentMovingPoint;
        float randomDirDown = Randomize::rand.RandomInt(-60, 60);

        sf::Vector2f choosenDir = Math::spinPoint(dirToCenter, sf::Vector2f(0, 0), randomDirDown);
        sf::Vector2f choosenMovement = Math::scaleVec(Math::normalizeVec(choosenDir), this->particleSpeed);

        this->currentMovingPoint += choosenMovement;
        this->currentMovingPoint.x = Math::clamp(start, end, this->currentMovingPoint.x);
    }
}

void Brownian::Visualize(sf::Event event) {
    //draw everything
    for (auto point: this->currentStickedPoints) {
        DrawUtils::drawCircle(this->window, GameManager::convertWorldToScreen(point), this->particleRadius, sf::Color::White);
    }
    DrawUtils::drawCircle(this->window, GameManager::convertWorldToScreen(this->currentMovingPoint), this->particleRadius, sf::Color::White);
}

void Brownian::LateUpdate() {

}

void Brownian::Reset() {
    points.clear();
    currentStickedPoints.clear();
}