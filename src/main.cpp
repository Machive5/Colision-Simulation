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
    
    Control control(&ControlWindow, &Window, &balls);

    Window.setPosition(sf::Vector2i(200, 100));
    ControlWindow.setPosition(sf::Vector2i(1200, 100));

    
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
                float nextDistance = sqrt(pow((balls[i].pos.x + balls[i].vel.x)  - (balls[j].pos.x + balls[i].vel.x), 2) + pow((balls[i].pos.y + balls[i].vel.y)  - (balls[j].pos.y + balls[i].vel.y), 2));
                float combineRadius = balls[i].mass + balls[j].mass;

                if (nextDistance >= combineRadius) continue;

                sf::Vector2f calcVelI = ((balls[i].mass - balls[j].mass)*balls[i].vel + 2*balls[j].mass*balls[j].vel)/(combineRadius);
                sf::Vector2f calcVelJ = ((balls[j].mass - balls[i].mass)*balls[j].vel + 2*balls[i].mass*balls[i].vel)/(combineRadius);

                float CalcVelIMag = sqrt(calcVelI.x*calcVelI.x + calcVelI.y*calcVelI.y);

                balls[i].vel = calcVelI;
                balls[j].vel = calcVelJ;


            }
        }

        for (int i = 0; i < balls.size(); i++){
            balls[i].update();
        }
        
        Window.display();
        ControlWindow.display();
        sf::sleep(sf::milliseconds(16));
    }
}