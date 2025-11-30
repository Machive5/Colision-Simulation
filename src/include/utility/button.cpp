#ifndef BUTTON_CPP
#define BUTTON_CPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

using namespace std;


class Button {
    private:
    sf::Font font;
    sf::Text label;
    sf::RectangleShape shape;
    
    using CallbackType = std::function<void()>;
    CallbackType callback = nullptr;
    
    
    public:
        Button(sf::Vector2f size, sf::Vector2f position, sf::Color color, string text, CallbackType cb): 
        font(),
        label(font)
        {
            
            if (!font.openFromFile("../assets/JAi.ttf")) {
                cout << "Failed to load font!" << endl;
            }

            shape.setSize(size);
            shape.setPosition(position);
            shape.setFillColor(color);
            shape.setOutlineColor(sf::Color::Transparent);
            shape.setOutlineThickness(2);
            shape.setOrigin({size.x / 2, size.y / 2});

            label.setFont(font);
            label.setString(text);
            label.setCharacterSize(24);
            label.setFillColor(sf::Color::White);
            label.setPosition(position);
            label.setOrigin({label.getLocalBounds().size.x / 2, label.getLocalBounds().size.y});

            callback = cb;
        }

        void setText(string text) {
            label.setString(text);
        }

        void render(sf::RenderWindow *window) {
            window->draw(shape);
            window->draw(label);
        }

        void update(sf::Vector2f mousePos, bool isClicked) {
            if (shape.getGlobalBounds().contains(mousePos)) {
                shape.setOutlineColor(sf::Color::White);
                if (isClicked) {
                    if (callback) {
                        callback();
                    }
                    return;
                }
            } else {
                shape.setOutlineColor(sf::Color::Transparent);
            }
        }

};
#endif