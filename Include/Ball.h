#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<bits/stdc++.h>
using namespace std;
using namespace sf;

class Ball {
public:
    CircleShape shape;

    Ball(float radius) {
        shape.setRadius(radius);
        shape.setFillColor(Color::Red);
    }

    void setPosition(float x, float y) {
        shape.setPosition(x, y);
    }

    void move(float offsetX, float offsetY) {
        shape.move((0.5*offsetX), (0.5*offsetY));
    }
};