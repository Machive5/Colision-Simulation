#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "include/ball.cpp"
#include "include/control.cpp"
#include <iostream>

int main(){
    srand(time(0));

    sf::RenderWindow Window(sf::VideoMode({800,600}), "SFML Render Window");
    sf::RenderWindow ControlWindow(sf::VideoMode({500,500}), "Control Panel");
    vector<Ball> balls;
    
    Control control(&ControlWindow, &Window, &balls);
    
    while (Window.isOpen()){
        while (optional<sf::Event> event = Window.pollEvent()){
            if (event->is<sf::Event::Closed>()){
                Window.close();
            }
        }

        Window.clear(sf::Color::Black);
        
        control.update();

        for (int i = 0; i < balls.size(); i++){
            balls[i].update();
        }
        
        Window.display();
        ControlWindow.display();

        sf::sleep(sf::milliseconds(16));
    }
}