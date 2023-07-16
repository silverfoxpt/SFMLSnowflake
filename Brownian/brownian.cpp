#include "brownian.h"

void Brownian::Initialize(sf::RenderWindow* window) {
    this->window = window;
    this->centerPoint = GameManager::convertScreenToWorld(center);
    this->vertices = sf::VertexArray(sf::Triangles);

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
    if (this->points.empty() && BrownianTravelPhase::Waiting) {
        return;
    }

    if (this->phase == BrownianTravelPhase::Waiting) { //start a new point travelling!
        sf::Vector2f point = this->points.back(); this->points.pop_back();
        this->currentMovingPoint = point;

        this->phase = BrownianTravelPhase::Travelling;
    } else { //travelling!
        //check if intersect any sticky circle
        for (auto stick: this->currentStickedPoints) {
            if (Math::CircleIntersect(stick, this->detectionRadius, this->currentMovingPoint, this->detectionRadius)) { //finished travelling!
                this->currentStickedPoints.push_back(this->currentMovingPoint);
                this->phase = BrownianTravelPhase::Waiting;

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
        float angleOfMovement = 360.0 / this->totalNumQuadrant / 2;
        float start = this->centerPoint.x;
        float end = this->centerPoint.x + std::tan(Math::toRad(angleOfMovement)) * std::abs(this->currentMovingPoint.y - GameManager::convertScreenToWorld(this->center).y);

        sf::Vector2f dirToCenter = this->centerPoint - this->currentMovingPoint;
        float randomDirDown = Randomize::rand.RandomInt(-60, 90);

        sf::Vector2f choosenDir = Math::spinPoint(dirToCenter, sf::Vector2f(0, 0), randomDirDown);
        sf::Vector2f choosenMovement = Math::scaleVec(Math::normalizeVec(choosenDir), this->particleSpeed);

        this->currentMovingPoint += choosenMovement;
        this->currentMovingPoint.x = Math::clamp(start, end, this->currentMovingPoint.x);
    }
}

void Brownian::Visualize(sf::Event event) {
    //draw everything
    float anglePerQuandrant = 360.0 / this->totalNumQuadrant;
    sf::VertexArray circleVertices(sf::Triangles);

    //normal points
    for (auto point: this->currentStickedPoints) {
        for (int i = 0; i < this->totalNumQuadrant; i++) {
            sf::Vector2f correctPoint = Math::spinPoint(point, this->centerPoint, anglePerQuandrant * i);
            //DrawUtils::drawCircle(this->window, GameManager::convertWorldToScreen(correctPoint), this->particleRadius, sf::Color::White);

            this->CalculateVertices(circleVertices, correctPoint, sf::Color::White);
        }   
    }

    //mirror points
    for (auto point: this->currentStickedPoints) {
        for (int i = 0; i < this->totalNumQuadrant; i++) {
            sf::Vector2f correctPoint = Math::spinPoint(point, this->centerPoint, anglePerQuandrant * i);

            //mirror angle
            float curAngle = Math::angleBetweenVectors(Math::getUpVec(), correctPoint - this->centerPoint);
            float mirrorAngle = Math::mirrorAngle(curAngle, anglePerQuandrant * i);
            
            sf::Vector2f pointAtUpVec = Math::scaleVec(Math::getUpVec(), Math::Length(correctPoint - this->centerPoint));
            sf::Vector2f originalUpPoint = this->centerPoint + pointAtUpVec;

            sf::Vector2f correctPoint2 = Math::spinPoint(originalUpPoint, this->centerPoint, mirrorAngle);
            this->CalculateVertices(circleVertices, correctPoint2, sf::Color::Red);
        }   
    }

    DrawUtils::drawCircle(this->window, GameManager::convertWorldToScreen(this->currentMovingPoint), this->particleRadius, sf::Color::White);
    this->window->draw(circleVertices);
}

void Brownian::LateUpdate() {

}

void Brownian::Reset() {
    points.clear();
    currentStickedPoints.clear();
    vertices.clear();
}

void Brownian::CalculateVertices(sf::VertexArray &arr, sf::Vector2f point, sf::Color color) {
    float radius = this->particleRadius;

    // Calculate the coordinates of the hexagon vertices
    /*std::vector<sf::Vector2f> hexagonVertices;
    for (int j = 0; j < 6; j++) {
        float angle = 2 * M_PI / 6 * (j + 0.5);
        sf::Vector2f vertex(point.x + radius * std::cos(angle),
                            point.y + radius * std::sin(angle));
        hexagonVertices.push_back(GameManager::convertWorldToScreen(vertex));
    }

    // Define the vertices for the hexagon shape
    for (int j = 1; j < 6 - 1; j++) {
        sf::Vertex vertex1(hexagonVertices[0], color);
        sf::Vertex vertex2(hexagonVertices[j], color);
        sf::Vertex vertex3(hexagonVertices[j + 1], color);

        // Add the vertices to the vertex array
        arr.append(vertex1);
        arr.append(vertex2);
        arr.append(vertex3);
    }*/

    // Define vertices for a triangle representing a circle
    sf::Vertex vertex1(GameManager::convertWorldToScreen(point), color);
    sf::Vertex vertex2(GameManager::convertWorldToScreen(point + sf::Vector2f(radius, 0)), color);
    sf::Vertex vertex3(GameManager::convertWorldToScreen(point + sf::Vector2f(0, radius)), color);

    // Add the vertices to the vertex array
    arr.append(vertex1);
    arr.append(vertex2);
    arr.append(vertex3);
}