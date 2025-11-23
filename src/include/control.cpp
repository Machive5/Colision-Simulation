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
    Button addBall;
    Button removeBall;
    Button addGravity;
    Button removeGravity;

    sf::Font font;
    sf::Text ballAmountText;
    sf::Text gravityText;


    sf::RenderWindow *window;
    sf:: RenderWindow *mainWindow;

    vector<Ball> *balls;
    int ballAmount = 0;
    float *gravity = 0;
    
    public:
        
        Control(sf::RenderWindow *win, sf::RenderWindow *mainWindow, vector<Ball> *balls, float *gravity):
            applyButton(sf::Vector2f(100,50), sf::Vector2f(250, 240), sf::Color::Blue, "generate", [this, balls, mainWindow](){
                vector<Ball> newBalls;
                for (int i = 0; i < ballAmount; i++){
                    // srand(static_cast<unsigned int>(time(0)) + i);
                    newBalls.push_back(Ball(mainWindow, rand() % 20 + 10));
                    cout << "Ball " << i << " Created on pos " << newBalls[i].pos.x << " " << newBalls[i].pos.y << endl;
                }
                *balls = newBalls;
            }),
            addBall(sf::Vector2f(50,50), sf::Vector2f(400, 100), sf::Color::Green, " (+) ", [this](){
                ballAmount += 10;
                if (ballAmount > 150) ballAmount = 150;
            }),
            removeBall(sf::Vector2f(50,50), sf::Vector2f(400, 160), sf::Color::Red, " (-) ", [this](){
                ballAmount -= 10;

                if (ballAmount < 0) ballAmount = 0;
            }),
            addGravity(sf::Vector2f(50,50), sf::Vector2f(400, 330), sf::Color::Green, " (+) ", [this, gravity](){
                *gravity += 0.1f;
                if (*gravity > 10.0f) *gravity = 10.0f;
            }),
            removeGravity(sf::Vector2f(50,50), sf::Vector2f(400, 390), sf::Color::Red, " (-) ", [this, gravity](){
                *gravity -= 0.1f;
                if (*gravity < 0.0f) *gravity = 0.0f;
            }),
            font(),
            ballAmountText(font),
            gravityText(font)
        {
            window = win;
            this->mainWindow = mainWindow;
            this->balls = balls;
            this->gravity = gravity;

            if (!font.openFromFile("../assets/JAi.ttf")) {
                cout << "Failed to load font!" << endl; 
            }

            ballAmountText.setFont(font);
            ballAmountText.setString("Number of Balls: " + to_string(balls->size()));
            ballAmountText.setCharacterSize(24);
            ballAmountText.setFillColor(sf::Color::White);
            ballAmountText.setPosition(sf::Vector2f(100, 115));

            gravityText.setFont(font);
            gravityText.setString("Gravity: " + to_string(*gravity));
            gravityText.setCharacterSize(24);
            gravityText.setFillColor(sf::Color::White);
            gravityText.setPosition(sf::Vector2f(100, 344));
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
                addBall.update(sf::Vector2f(sf::Mouse::getPosition(*window)), sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                removeBall.update(sf::Vector2f(sf::Mouse::getPosition(*window)), sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));

                addGravity.update(sf::Vector2f(sf::Mouse::getPosition(*window)), sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
                removeGravity.update(sf::Vector2f(sf::Mouse::getPosition(*window)), sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
            }

            ballAmountText.setString("Number of Balls: " + to_string(ballAmount));
            gravityText.setString("Gravity: " + to_string(*gravity));

            applyButton.render(window);
            addBall.render(window);
            removeBall.render(window);

            addGravity.render(window);
            removeGravity.render(window);

            window->draw(ballAmountText);
            window->draw(gravityText);
        }
};