#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<bits/stdc++.h>
using namespace std;
using namespace sf;

class Brick {
public:
    Sprite sprite;

    Brick(Texture &texture) 
    {
        sprite.setTexture(texture);
    }

    void setPosition(float x, float y) 
    {
        sprite.setPosition(x, y);
    }
};

const int numBricksX = 12;
const int numBricksY = 5;
vector<Brick> bricks;

double brickWidth = 0.2;
double brickHeight = 0.1;