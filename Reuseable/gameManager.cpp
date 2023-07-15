#include "gameManager.h"

sf::Vector2u GameManager::originalResolution = sf::Vector2u(1920, 1080);

sf::Vector2f GameManager::convertWorldToScreen(sf::Vector2f world) {
    return sf::Vector2f(world.x, -world.y);
}

sf::Vector2f GameManager::convertScreenToWorld(sf::Vector2f screen) {
    return sf::Vector2f(screen.x, -screen.y);
}

void GameManager::InitializeWindowWithResolution(sf::RenderWindow* mainWindow) {
    sf::Vector2u currentResolution = sf::Vector2u(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
    
    // Calculate the scale factors
    float scaleX = static_cast<float>(currentResolution.x) / originalResolution.x;
    float scaleY = static_cast<float>(currentResolution.y) / originalResolution.y;

    // Scale the main window size
    sf::Vector2u windowSize(static_cast<unsigned int>(mainWindow->getSize().x * scaleX),
                            static_cast<unsigned int>(mainWindow->getSize().y * scaleY));
    mainWindow->setSize(windowSize);
}