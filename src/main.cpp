#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "include/ball.cpp"
#include "include/control.cpp"
#include <iostream>
#include <math.h>

int main(){
    srand(time(0));

    sf::RenderWindow Window(sf::VideoMode({800,600}), "SFML Render Window");
    sf::RenderWindow ControlWindow(sf::VideoMode({500,500}), "Control Panel");
    vector<Ball> balls;
    
    
    Window.setPosition(sf::Vector2i(200, 100));
    ControlWindow.setPosition(sf::Vector2i(1200, 100));
    
    float gravity = 0.5f;
    
    Control control(&ControlWindow, &Window, &balls, &gravity);
    
    while (Window.isOpen()){
        while (optional<sf::Event> event = Window.pollEvent()){
            if (event->is<sf::Event::Closed>()){
                Window.close();
            }
        }

        Window.clear(sf::Color::Black);
        control.update();

        for (int i = 0; i  < balls.size(); i++){
            for (int j = i+1; j < balls.size(); j++){
                float distance = sqrt(pow(balls[i].pos.x - balls[j].pos.x, 2) + pow(balls[i].pos.y - balls[j].pos.y, 2));
                float combineRadius = balls[i].mass + balls[j].mass;
                float overlap = combineRadius - distance;

                if (overlap < 0) continue;

                balls[i].pos += (balls[i].pos - balls[j].pos) / distance * (overlap / 2.0f);
                balls[j].pos += (balls[j].pos - balls[i].pos) / distance * (overlap / 2.0f);

                sf::Vector2f calcVelI = ((balls[i].mass - balls[j].mass)*balls[i].vel + 2*balls[j].mass*balls[j].vel)/(combineRadius);
                sf::Vector2f calcVelJ = ((balls[j].mass - balls[i].mass)*balls[j].vel + 2*balls[i].mass*balls[i].vel)/(combineRadius);

                balls[i].vel = calcVelI;
                balls[j].vel = calcVelJ;
            }
        }

        for (int i = 0; i < balls.size(); i++){
            balls[i].acc = sf::Vector2f(0, gravity);
            balls[i].update();
        }
        
        Window.display();
        ControlWindow.display();
        sf::sleep(sf::milliseconds(16));
    }
}