#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "include/ball.cpp"
#include "include/control.cpp"
#include "include/utility/quadTree.cpp"
#include <iostream>
#include <math.h>
#include <chrono>

void bruteforce(vector<Ball> &balls){
    for (int i = 0; i  < balls.size(); i++){
        for (int j = i+1; j < balls.size(); j++){
            float distance = sqrt(pow(balls[i].pos.x - balls[j].pos.x, 2) + pow(balls[i].pos.y - balls[j].pos.y, 2));
            float combineRadius = balls[i].radius + balls[j].radius;
            float overlap = combineRadius - distance;

            if (overlap < 0) continue;

            if (distance == 0) {
                distance = 0.1f;
            }

            balls[i].pos += (balls[i].pos - balls[j].pos) / distance * (overlap / 2.0f);
            balls[j].pos += (balls[j].pos - balls[i].pos) / distance * (overlap / 2.0f);

            sf::Vector2f calcVelI = ((balls[i].radius - balls[j].radius)*balls[i].vel + 2*balls[j].radius*balls[j].vel)/(combineRadius);
            sf::Vector2f calcVelJ = ((balls[j].radius - balls[i].radius)*balls[j].vel + 2*balls[i].radius*balls[i].vel)/(combineRadius);

            balls[i].vel = calcVelI;
            balls[j].vel = calcVelJ;
        }
    }

}

void quadTreeCollision(vector<Ball> &balls){
    QuadTree qt(sf::FloatRect({0,0},{800,600}), 4);

    for (int i = 0; i < balls.size(); i++){
        qt.insert(&balls[i]);
    }

    for (int i = 0; i < balls.size(); i++){
        vector<Ball*> found;
        sf::FloatRect range(
            {
                balls[i].pos.x - balls[i].radius*3.5f,
                balls[i].pos.y - balls[i].radius*3.5f
            },
            {
                balls[i].radius*5,
                balls[i].radius*5
            }
        );

        qt.query(range, found);

        for (int j = 0; j < found.size(); j++){
            if (&balls[i] == found[j]) continue;

            float distance = sqrt(pow(balls[i].pos.x - found[j]->pos.x, 2) + pow(balls[i].pos.y - found[j]->pos.y, 2));
            float combineRadius = balls[i].radius + found[j]->radius;
            float overlap = combineRadius - distance;

            if (overlap < 0) continue;

            if (distance == 0) {
                distance = 0.1f;
            }

            balls[i].pos += (balls[i].pos - found[j]->pos) / distance * (overlap / 2.0f);
            balls[j].pos += (balls[i].pos - found[j]->pos) / distance * (overlap / 2.0f);

            sf::Vector2f calcVelI = ((balls[i].radius - found[j]->radius)*balls[i].vel + 2*found[j]->radius*found[j]->vel)/(combineRadius);
            sf::Vector2f calcVelJ = ((found[j]->radius - balls[i].radius)*found[j]->vel + 2*balls[i].radius*balls[i].vel)/(combineRadius);

            balls[i].vel = calcVelI;
            found[j]->vel = calcVelJ;
        }

    }
}

int main(){
    srand(time(0));

    sf::RenderWindow Window(sf::VideoMode({800,600}), "SFML Render Window");
    sf::RenderWindow ControlWindow(sf::VideoMode({500,500}), "Control Panel");
    vector<Ball> balls;
    
    
    Window.setPosition(sf::Vector2i(200, 100));
    ControlWindow.setPosition(sf::Vector2i(1200, 100));
    
    float gravity = 0.0f;
    bool Mode = false;
    
    Control control(&ControlWindow, &Window, &balls, &gravity, &Mode);
    
    while (Window.isOpen()){
        chrono::time_point<std::chrono::system_clock> start = chrono::system_clock::now();
        while (optional<sf::Event> event = Window.pollEvent()){
            if (event->is<sf::Event::Closed>()){
                Window.close();
            }
        }

        Window.clear(sf::Color::Black);
        control.update();

        if (Mode){
            quadTreeCollision(balls);
        } else {
            bruteforce(balls);
        }

        for (int i = 0; i < balls.size(); i++){
            balls[i].acc = sf::Vector2f(0, gravity);
            balls[i].update();
        }
        
        Window.display();
        ControlWindow.display();
        chrono::time_point<std::chrono::system_clock> end = chrono::system_clock::now();
        chrono::duration elapsed = end - start;

        cout << "elapsed time: " << chrono::duration_cast<chrono::microseconds>(elapsed).count()*0.000001f << " s" << endl;

        sf::sleep(sf::milliseconds(16));
    }
}