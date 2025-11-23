#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include "ball.cpp"
#include "utility/button.cpp"
// #include "utility/inputfield.cpp"

using namespace std;

class Control {
    private:
    Button applyButton;
    Button add;
    Button remove;

    sf::Font font;
    sf::Text jumlah;
    sf::RenderWindow *window;
    sf:: RenderWindow *mainWindow;

    vector<Ball> *balls;
    int ballCount = 0;
    
    public:
        
        Control(sf::RenderWindow *win, sf::RenderWindow *mainWindow, vector<Ball> *balls):
            applyButton(sf::Vector2f(100,50), sf::Vector2f(250, 433), sf::Color::Blue, "Apply", [this, balls, mainWindow](){
                vector<Ball> newBalls;
                for (int i = 0; i < ballCount; i++){
                    // srand(static_cast<unsigned int>(time(0)) + i);
                    newBalls.push_back(Ball(mainWindow, rand() % 20 + 10));
                    cout << "Ball " << i << " Created on pos " << newBalls[i].pos.x << " " << newBalls[i].pos.y << endl;
                }
                *balls = newBalls;
            }),
            add(sf::Vector2f(50,50), sf::Vector2f(400, 100), sf::Color::Green, " (+) ", [this](){
                ballCount += 10;
                if (ballCount > 500) ballCount = 500;
            }),
            remove(sf::Vector2f(50,50), sf::Vector2f(400, 160), sf::Color::Red, " (-) ", [this](){
                ballCount -= 10;

                if (ballCount < 0) ballCount = 0;
            }),
            font(),
            jumlah(font)
        {
            window = win;
            mainWindow = mainWindow;
            this->balls = balls;

            if (!font.openFromFile("../assets/JAi.ttf")) {
                cout << "Failed to load font!" << endl; 
            }

            jumlah.setFont(font);
            jumlah.setString("Number of Balls: " + to_string(balls->size()));
            jumlah.setCharacterSize(24);
            jumlah.setFillColor(sf::Color::White);
            jumlah.setPosition(sf::Vector2f(100, 115));
        }

        void update(){
            window->clear(sf::Color(50,50,50));
            while (optional<sf::Event> event = window->pollEvent()){
                if (event->is<sf::Event::Closed>()){
                    window->close();
                    mainWindow->close();
                }

                if (event->is<sf::Event::MouseButtonPressed>()){
                    cout << "mouse pos: " << sf::Mouse::getPosition(*window).x << " " << sf::Mouse::getPosition(*window).y << endl;
                }
                applyButton.update(sf::Vector2f(sf::Mouse::getPosition(*window)), sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                add.update(sf::Vector2f(sf::Mouse::getPosition(*window)), sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                remove.update(sf::Vector2f(sf::Mouse::getPosition(*window)), sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
            }

            jumlah.setString("Number of Balls: " + to_string(ballCount));

            applyButton.render(window);
            add.render(window);
            remove.render(window);
            window->draw(jumlah);
        }
};