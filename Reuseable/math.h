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

#include "randomsfml.h"

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

        //clockwise
        static sf::Vector2f spinPoint(const sf::Vector2f point, const sf::Vector2f center, float angleDegrees) {
            //if (angleDegrees < 0 || angleDegrees > 360) { std::cout << "Wrong angle"; return getUpVec();}
            if (angleDegrees < 0) {
                angleDegrees = 360 + angleDegrees;
            }
            angleDegrees = 360 - angleDegrees; //clockwise it

            sf::Transform transform;
            transform.translate(center);
            transform.rotate(angleDegrees);
            transform.translate(-center);

            return transform.transformPoint(point);
        }

        static sf::Vector2f convertToFloatVec(sf::Vector2i a) {
            return sf::Vector2f(a.x, a.y);
        }

        static sf::Vector2f getUpVec() {
            return sf::Vector2f(0, 1);
        }

        static sf::Vector2f scaleVec(sf::Vector2f vec, float factor) {
            return vec * factor;
        }

        static sf::Vector2f normalizeVec(sf::Vector2f vec) {
            return scaleVec(vec, 1.0/Length(vec));
        }

        static sf::Vector2f getDirectionVecWithAngle(float angle) {
            if (angle < 0 || angle > 360) {std::cout << "Invalid angle!"; return getUpVec();}

            sf::Vector2f spinVec = spinPoint(getUpVec(), sf::Vector2f(0, 0), angle);
            return spinVec;
        }

        static sf::Vector2f getRandomDirectionVecWithAngleRange(float angleMin, float angleMax) {
            if (angleMin < 0 || angleMax > 360 || angleMin > angleMax) {std::cout << "Invalid random range angle!"; return getUpVec();}
            
            float randomAngle = Randomize::rand.RandomInt((int) angleMin, (int) angleMax);
            return getDirectionVecWithAngle(randomAngle);
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

        static bool CircleIntersect(sf::Vector2f center1, float rad1, sf::Vector2f center2, float rad2) {
            // Calculate the distance between the centers of the circles
            float distance = Distance(center1, center2);

            // Check if the distance is less than the sum of the radii
            if (distance <= rad1 + rad2) {
                // Circles intersect
                return true;
            }

            // Circles do not intersect
            return false;
        }

        static float toRad(float degree) {
            return degree * (M_PI / 180.0);
        }

        static float clamp(float start, float end, float value) {
            if (start > end) {std::cout << "Clamp Error" << '\n'; return value; }
            value = std::max(value, start);
            value = std::min(value, end);

            return value;
        }

        static float mirrorAngle(float angle, float rootAngle) {
            // Normalize the angles to the range [0, 360)
            angle = std::fmod(angle, 360.0f);
            rootAngle = std::fmod(rootAngle, 360.0f);

            // Calculate the mirrored angle
            float mirroredAngle = 2.0f * rootAngle - angle;

            // Normalize the mirrored angle to the range [0, 360)
            mirroredAngle = std::fmod(mirroredAngle, 360.0f);
            if (mirroredAngle < 0.0f) {
                mirroredAngle += 360.0f;
            }

            return mirroredAngle;
        }

        //always clockwise
        static float angleBetweenVectors(const sf::Vector2f& v1, const sf::Vector2f& v2) {
            float dot = v1.x * v2.x + v1.y * v2.y;
            float det = v1.x * v2.y - v1.y * v2.x;
            float angle = std::atan2(det, dot) * 180.0f / M_PI;

            if (angle < 0.0f) {
                angle += 360.0f;
            }

            return 360.0f - angle;
        }
};

#endif