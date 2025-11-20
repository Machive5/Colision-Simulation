#ifndef BALL_CPP
#define BALL_CPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

using namespace std;

class Ball {
    private:
        sf::CircleShape shape;
        sf::RenderWindow* window;

        sf::Color randomColor(){
            float r = rand() % 256;
            float g = rand() % 256;
            float b = rand() % 256;
            return sf::Color(r, g, b);
        }
        
        void bounceOffWalls(){
            if ((pos.x+vel.x) - w < 0 || (pos.x + vel.x) + w > window->getSize().x){
                vel.x = -vel.x;
            }
            if ((pos.y + vel.y) - w < 0 || (pos.y + vel.y) + w > window->getSize().y){
                vel.y = -vel.y;
            }
        }

    public:
        float w;
        sf::Vector2f vel;
        sf::Vector2f acc;
        sf::Vector2f pos;

        Ball(sf::RenderWindow *win, float weight){
            window = win;
            w = weight;
            shape.setRadius(w);
            shape.setFillColor(randomColor());

            pos = sf::Vector2f(rand() % (window->getSize().x - (int)(2*w)) + w, rand() % (window->getSize().y - (int)(2*w)) + w);
            vel = sf::Vector2f(rand() % 10, rand() %10);
            acc = sf::Vector2f(0,0);
            shape.setPosition(pos);
            shape.setOrigin(sf::Vector2f(w, w));
        }

        void update(){
            vel += acc;
            bounceOffWalls();
            pos += vel;
            shape.setPosition(pos);
            window->draw(shape);
        }
};
#endif