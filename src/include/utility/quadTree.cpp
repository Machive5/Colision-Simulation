#ifndef QUADTREE_CPP
#define QUADTREE_CPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "../ball.cpp"

using namespace std;

class QuadTree {
    private:
        sf::FloatRect boundary;
        int capacity;
        vector<Ball*> balls;
        bool divided = false;

        QuadTree *northeast = nullptr;
        QuadTree *northwest = nullptr;
        QuadTree *southeast = nullptr;
        QuadTree *southwest = nullptr;

        void subdivide() {
            float x = boundary.position.x;
            float y = boundary.position.y;
            float w = boundary.size.x / 2;
            float h = boundary.size.y / 2;

            northeast = new QuadTree(sf::FloatRect({x + w, y}, {w, h}), capacity);
            northwest = new QuadTree(sf::FloatRect({x, y}, {w, h}), capacity);
            southeast = new QuadTree(sf::FloatRect({x + w, y + h}, {w, h}), capacity);
            southwest = new QuadTree(sf::FloatRect({x, y + h}, {w, h}), capacity);

            divided = true;
        }

    public:    
        void insert(Ball* ball) {
            if (!boundary.contains(ball->pos)) {
                return;
            }

            if (balls.size() < capacity) {
                balls.push_back(ball);
            } 
            
            else {
                if (!divided) {
                    subdivide();
                }

                northeast->insert(ball);
                northwest->insert(ball);
                southeast->insert(ball);
                southwest->insert(ball);
            }
        }

        void clear(){
            balls.clear();
            if (divided){
                northeast->clear();
                northwest->clear();
                southeast->clear();
                southwest->clear();

                delete northeast;
                delete northwest;
                delete southeast;
                delete southwest;

                divided = false;
            }
        }

        void query(sf::FloatRect range, vector<Ball*> &found) {
            if (!boundary.findIntersection(range)) {
                return;
            }

            for (Ball* ball : balls) {
                if (range.contains(ball->pos)) {
                    found.push_back(ball);
                }
            }

            if (divided) {
                northeast->query(range, found);
                northwest->query(range, found);
                southeast->query(range, found);
                southwest->query(range, found);
            }
        }


    public:
        QuadTree(sf::FloatRect boundary, int capacity) : boundary(boundary), capacity(capacity) {}
};

#endif