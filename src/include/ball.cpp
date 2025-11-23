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
            if (pos.x - mass < 0){
                pos.x = mass;
                vel.x = -vel.x;
            }
            if (pos.x + mass > window->getSize().x){
                pos.x = window->getSize().x - mass;
                vel.x = -vel.x;
            }

            if (pos.y - mass < 0){
                pos.y = mass;
                vel.y = -vel.y;
            }
            if (pos.y + mass > window->getSize().y){
                pos.y = window->getSize().y - mass;
                vel.y = -vel.y;
            }
        }

    public:
        float mass;
        sf::Vector2f vel;
        sf::Vector2f acc;
        sf::Vector2f pos;
        sf::Vector2f momentum;
        sf::CircleShape shape;

        Ball(sf::RenderWindow *win, float mass){
            window = win;
            this->mass = mass;
            shape.setRadius(mass);
            shape.setFillColor(randomColor());

            pos = sf::Vector2f(rand() % (window->getSize().x - (int)(2*mass)) + mass, rand() % (window->getSize().y - (int)(2*mass)) + mass);
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