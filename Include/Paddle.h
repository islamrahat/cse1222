#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<bits/stdc++.h>
using namespace std;
using namespace sf;

class Paddle {
public:
    Sprite sprite;

    Paddle(Texture &texture) 
    {
        sprite.setTexture(texture);
    }

    void setPosition(float x, float y) 
    {
        sprite.setPosition(x, y);
    }

    void move(float offsetX, float offsetY) 
    {
        sprite.move((0.5*offsetX), (0.5*offsetY));
    }
};


float paddleWidth = 0.0002;
float paddleHeight = 0.00001;