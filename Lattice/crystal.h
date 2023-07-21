#ifndef H_CRYSTAL
#define H_CRYSTAL

#include <SFML/Graphics.hpp>

#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <memory>
#include <chrono>
#include <vector>
#include <set>
#include <unordered_set>

#include "../Reuseable/templateclass.h"
#include "../Reuseable/math.h"
#include "../Reuseable/drawshapes.h"
#include "../Reuseable/gameManager.h"

#include "lattice.h"

struct PairHash {
    std::size_t operator()(const std::pair<int, int>& p) const {
        std::size_t h1 = std::hash<int>{}(p.first);
        std::size_t h2 = std::hash<int>{}(p.second);

        // Combine the hash codes using bitwise XOR
        return h1 ^ h2;
    }
};

class Crystal: Monobehaviour<sf::RenderWindow*, HexagonLattice*> {
    public:
        sf::RenderWindow* window;
        HexagonLattice* lattice;

        int cols;
        int rows;

        //values
        std::vector<std::vector<int>> a;
        std::vector<std::vector<float>> b;
        std::vector<std::vector<float>> c;
        std::vector<std::vector<float>> d;
        //std::vector<std::vector<float>> d2;

        std::unordered_set<std::pair<int, int>, PairHash> inside;
        std::unordered_set<std::pair<int, int>, PairHash> boundary;
        std::unordered_set<std::pair<int, int>, PairHash> outside;
        std::unordered_set<std::pair<int, int>, PairHash> outsideBoundary;
        std::unordered_set<std::pair<int, int>, PairHash> all;

        std::vector<std::vector<std::vector<std::pair<int, int>>>> neighborIdx;

        //settings
        float p1 = 0.40; //original 0.35

        float k2 = 0.05;

        float b3 = 1.1; //original 1.4
        float o3 = 0.015;
        float a3 = 0.001;

        float u4 = 0.015;
        float y4 = 0.01;

        float o5 = 0.00005;

        void Initialize(sf::RenderWindow* window, HexagonLattice* lattice) override;
        void Update(sf::Event event) override;
        void Visualize(sf::Event event) override;
        void LateUpdate() override;
        void Reset() override;

        float* getP1() { return &this->p1; }
        float* getK2() { return &this->k2; }
        float* getB3() { return &this->b3; }
        float* getO3() { return &this->o3; }
        float* getA3() { return &this->a3; }
        float* getU4() { return &this->u4; }
        float* getY4() { return &this->y4; }
        float* getO5() { return &this->o5; }

    private:
        void Diffusion();
        void Freezing();
        void Attachment();
        void Melting();
        void Perturb();

        void AddToCrystal(int col, int row);
        void ModCrystalValue(int col, int row);

        sf::Color GetColorFromLightness(float lightness);
};

#endif