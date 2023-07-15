#ifndef H_MATH
#define H_MATH

#include <SFML/Graphics.hpp>

#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <memory>
#include <chrono>

class Math {
    public:
        static constexpr float Exponent = 7;

        static float DotProd(sf::Vector2f a, sf::Vector2f b) {
            return a.x * b.x + a.y * b.y;
        }

        static float Determinant(sf::Vector2f a, sf::Vector2f b) {
            return a.x * b.y - a.y * b.x;
        }

        static float Length(sf::Vector2f a) {
            return std::sqrt(a.x * a.x + a.y * a.y);
        }

        static float Distance(sf::Vector2f a, sf::Vector2f b) {
             return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
        }

        static sf::Vector2f Middlepoint(sf::Vector2f a, sf::Vector2f b) {
            return sf::Vector2f((a.x + b.x) / 2, (a.y + b.y) / 2);
        }

        static sf::Vector2f Lerp(sf::Vector2f a, sf::Vector2f b, float t) {
            if (t <= 0) {return a;}
            if (t >= 1) {return b;}

            float x = a.x + (b.x - a.x) * t;
            float y = a.y + (b.y - a.y) * t;
            return sf::Vector2f(x, y);
        }

        static sf::Vector2f spinPoint(const sf::Vector2f point, const sf::Vector2f center, float angleDegrees) {
            sf::Transform transform;
            transform.translate(center);
            transform.rotate(angleDegrees);
            transform.translate(-center);

            return transform.transformPoint(point);
        }

        static sf::Vector2f convertToFloatVec(sf::Vector2i a) {
            return sf::Vector2f(a.x, a.y);
        }

        static bool CheckSimilarPoint(sf::Vector2f a1, sf::Vector2f a2, bool debug = false) {
            const float epsilon = 0.001;
            if (std::abs(a1.x - a2.x) <= epsilon && std::abs(a1.y - a2.y) <= epsilon) {
                if (debug) {
                    //std::cout << "Similar!" << '\n';
                }
                return true;
            }
            return false;
        }

        static bool CheckSimilarNumber(float a, float b) {
            const float epsilon = 0.001;
            if (std::abs(a - b) <= epsilon) {
                return true;
            }
            return false;
        }

        //intersect of segments (not lines)
        //https://en.wikipedia.org/wiki/Line–line_intersection#Given_two_points_on_each_line 
        static sf::Vector2i Intersect(sf::Vector2f a1, sf::Vector2f a2, sf::Vector2f b1, sf::Vector2f b2, bool debug = false) {
            float x1 = a1.x, y1 = a1.y;
            float x2 = a2.x, y2 = a2.y;
            float x3 = b1.x, y3 = b1.y;
            float x4 = b2.x, y4 = b2.y;

            float t1 = (x1-x3) * (y3-y4) - (y1-y3) * (x3-x4);
            float t2 = (x1-x2) * (y3-y4) - (y1-y2) * (x3-x4);
            float t = t1/t2;

            float u1 = (x1-x3) * (y1-y2) - (y1-y3) * (x1-x2);
            float u2 = (x1-x2) * (y3-y4) - (y1-y2) * (x3-x4);
            float u = u1/u2;

            if (0 <= t && t <= 1 && 0 <= u && u <= 1) {
                return sf::Vector2i(x1 + t*(x2-x1), y1 + t*(y2-y1));
            }
            return sf::Vector2i(-99999, -99999);
        }
};

#endif