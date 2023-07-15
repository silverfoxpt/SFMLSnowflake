#ifndef H_TEMPLATECLASS
#define H_TEMPLATECLASS

#include <SFML/Graphics.hpp>

#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <memory>
#include <chrono>

template <typename... Args>
class Monobehaviour {
public:
    //virtual ~Monobehaviour() {}

    virtual void Initialize(Args... args)   = 0;
    virtual void Update(sf::Event event)    = 0;
    virtual void Visualize(sf::Event event) = 0;
    virtual void LateUpdate()               = 0;
    virtual void Reset()                    = 0;
};


#endif