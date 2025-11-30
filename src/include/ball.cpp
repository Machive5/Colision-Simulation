#ifndef BALL_CPP
#define BALL_CPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

using namespace std;

class Ball {
    private:
        sf::RenderWindow* window;

        sf::Color randomColor(){
            float r = rand() % 256;
            float g = rand() % 256;
            float b = rand() % 256;
            return sf::Color(r, g, b);
        }
        
        void bounceOffWalls(){
            if (pos.x - radius < 0){
                pos.x = radius;
                vel.x = -vel.x;
            }

            if (pos.x + radius > window->getSize().x){
                pos.x = window->getSize().x - radius;
                vel.x = -vel.x;
            }

            if (pos.y - radius < 0){
                pos.y = radius;
                vel.y = -vel.y;
            }
            if (pos.y + radius > window->getSize().y){
                pos.y = window->getSize().y - radius;
                vel.y = -vel.y;
            }
        }

    public:
        float mass;
        float radius;
        sf::Vector2f vel;
        sf::Vector2f acc;
        sf::Vector2f pos;
        sf::Vector2f momentum;
        sf::CircleShape shape;

        Ball(sf::RenderWindow *win, float mass){
            window = win;
            this->mass = mass;
            this->radius = mass * 0.3f;
            shape.setRadius(radius);
            shape.setFillColor(randomColor());

            pos = sf::Vector2f(rand() % (window->getSize().x - (int)(2*radius)) + radius, rand() % (window->getSize().y - (int)(2*radius)) + radius);
            vel = sf::Vector2f(rand() % 10, rand() %10);
            acc = sf::Vector2f(0,0);
            momentum = sf::Vector2f(mass*vel.x, mass*vel.y);
            shape.setPosition(pos);
            shape.setOrigin(sf::Vector2f(mass, mass));
        }

        void update(){
            bounceOffWalls();

            vel += acc;

            if (abs(vel.x) < 0.05) vel.x = 0;
            if (abs(vel.y) < 0.05) vel.y = 0;

            pos += vel;
            momentum = sf::Vector2f(mass*vel.x, mass*vel.y);
            shape.setPosition(pos);
            window->draw(shape);
        }
};
#endif