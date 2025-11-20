#ifndef TEXTINPUT_CPP
#define TEXTINPUT_CPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "button.cpp"

using namespace std;

class AdderInput{
    private :
    sf::Font font;
    sf::Text label;
    sf::Text nominal;
    Button add;
    Button subtract;

    public: 
    AdderInput(sf::Vector2f position, string text):
    font(),
    label(font),
    nominal(font),
    add(sf::Vector2f(30,30), sf::Vector2f(position.x + 60, position.y), sf::Color::Green, "+", 0),
    subtract(sf::Vector2f(30,30), sf::Vector2f(position.x - 60, position.y), sf::Color::Red, "-", 0)
    {
        if (!font.openFromFile("../assets/JAi.ttf")) {
            cout << "Failed to load font!" << endl; 
        }
    }
    
};

#endif